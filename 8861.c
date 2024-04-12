svc_process_common(struct svc_rqst *rqstp, struct kvec *argv, struct kvec *resv)
{
	struct svc_program	*progp;
	struct svc_version	*versp = NULL;	/* compiler food */
	struct svc_procedure	*procp = NULL;
	struct svc_serv		*serv = rqstp->rq_server;
	kxdrproc_t		xdr;
	__be32			*statp;
	u32			prog, vers, proc;
	__be32			auth_stat, rpc_stat;
	int			auth_res;
	__be32			*reply_statp;

	rpc_stat = rpc_success;

	if (argv->iov_len < 6*4)
		goto err_short_len;

	/* Will be turned off only in gss privacy case: */
	set_bit(RQ_SPLICE_OK, &rqstp->rq_flags);
	/* Will be turned off only when NFSv4 Sessions are used */
	set_bit(RQ_USEDEFERRAL, &rqstp->rq_flags);
	clear_bit(RQ_DROPME, &rqstp->rq_flags);

	/* Setup reply header */
	rqstp->rq_xprt->xpt_ops->xpo_prep_reply_hdr(rqstp);

	svc_putu32(resv, rqstp->rq_xid);

	vers = svc_getnl(argv);

	/* First words of reply: */
	svc_putnl(resv, 1);		/* REPLY */

	if (vers != 2)		/* RPC version number */
		goto err_bad_rpc;

	/* Save position in case we later decide to reject: */
	reply_statp = resv->iov_base + resv->iov_len;

	svc_putnl(resv, 0);		/* ACCEPT */

	rqstp->rq_prog = prog = svc_getnl(argv);	/* program number */
	rqstp->rq_vers = vers = svc_getnl(argv);	/* version number */
	rqstp->rq_proc = proc = svc_getnl(argv);	/* procedure number */

	for (progp = serv->sv_program; progp; progp = progp->pg_next)
		if (prog == progp->pg_prog)
			break;

	/*
	 * Decode auth data, and add verifier to reply buffer.
	 * We do this before anything else in order to get a decent
	 * auth verifier.
	 */
	auth_res = svc_authenticate(rqstp, &auth_stat);
	/* Also give the program a chance to reject this call: */
	if (auth_res == SVC_OK && progp) {
		auth_stat = rpc_autherr_badcred;
		auth_res = progp->pg_authenticate(rqstp);
	}
	switch (auth_res) {
	case SVC_OK:
		break;
	case SVC_GARBAGE:
		goto err_garbage;
	case SVC_SYSERR:
		rpc_stat = rpc_system_err;
		goto err_bad;
	case SVC_DENIED:
		goto err_bad_auth;
	case SVC_CLOSE:
		goto close;
	case SVC_DROP:
		goto dropit;
	case SVC_COMPLETE:
		goto sendit;
	}

	if (progp == NULL)
		goto err_bad_prog;

	if (vers >= progp->pg_nvers ||
	  !(versp = progp->pg_vers[vers]))
		goto err_bad_vers;

	/*
	 * Some protocol versions (namely NFSv4) require some form of
	 * congestion control.  (See RFC 7530 section 3.1 paragraph 2)
	 * In other words, UDP is not allowed. We mark those when setting
	 * up the svc_xprt, and verify that here.
	 *
	 * The spec is not very clear about what error should be returned
	 * when someone tries to access a server that is listening on UDP
	 * for lower versions. RPC_PROG_MISMATCH seems to be the closest
	 * fit.
	 */
	if (versp->vs_need_cong_ctrl &&
	    !test_bit(XPT_CONG_CTRL, &rqstp->rq_xprt->xpt_flags))
		goto err_bad_vers;

	procp = versp->vs_proc + proc;
	if (proc >= versp->vs_nproc || !procp->pc_func)
		goto err_bad_proc;
	rqstp->rq_procinfo = procp;

	/* Syntactic check complete */
	serv->sv_stats->rpccnt++;

	/* Build the reply header. */
	statp = resv->iov_base +resv->iov_len;
	svc_putnl(resv, RPC_SUCCESS);

	/* Bump per-procedure stats counter */
	procp->pc_count++;

	/* Initialize storage for argp and resp */
	memset(rqstp->rq_argp, 0, procp->pc_argsize);
	memset(rqstp->rq_resp, 0, procp->pc_ressize);

	/* un-reserve some of the out-queue now that we have a
	 * better idea of reply size
	 */
	if (procp->pc_xdrressize)
		svc_reserve_auth(rqstp, procp->pc_xdrressize<<2);

	/* Call the function that processes the request. */
	if (!versp->vs_dispatch) {
		/* Decode arguments */
		xdr = procp->pc_decode;
		if (xdr && !xdr(rqstp, argv->iov_base, rqstp->rq_argp))
			goto err_garbage;

		*statp = procp->pc_func(rqstp, rqstp->rq_argp, rqstp->rq_resp);

		/* Encode reply */
		if (*statp == rpc_drop_reply ||
		    test_bit(RQ_DROPME, &rqstp->rq_flags)) {
			if (procp->pc_release)
				procp->pc_release(rqstp, NULL, rqstp->rq_resp);
			goto dropit;
		}
		if (*statp == rpc_autherr_badcred) {
			if (procp->pc_release)
				procp->pc_release(rqstp, NULL, rqstp->rq_resp);
			goto err_bad_auth;
		}
		if (*statp == rpc_success &&
		    (xdr = procp->pc_encode) &&
		    !xdr(rqstp, resv->iov_base+resv->iov_len, rqstp->rq_resp)) {
			dprintk("svc: failed to encode reply\n");
			/* serv->sv_stats->rpcsystemerr++; */
			*statp = rpc_system_err;
		}
	} else {
		dprintk("svc: calling dispatcher\n");
		if (!versp->vs_dispatch(rqstp, statp)) {
			/* Release reply info */
			if (procp->pc_release)
				procp->pc_release(rqstp, NULL, rqstp->rq_resp);
			goto dropit;
		}
	}

	/* Check RPC status result */
	if (*statp != rpc_success)
		resv->iov_len = ((void*)statp)  - resv->iov_base + 4;

	/* Release reply info */
	if (procp->pc_release)
		procp->pc_release(rqstp, NULL, rqstp->rq_resp);

	if (procp->pc_encode == NULL)
		goto dropit;

 sendit:
	if (svc_authorise(rqstp))
		goto close;
	return 1;		/* Caller can now send it */

 dropit:
	svc_authorise(rqstp);	/* doesn't hurt to call this twice */
	dprintk("svc: svc_process dropit\n");
	return 0;

 close:
	if (test_bit(XPT_TEMP, &rqstp->rq_xprt->xpt_flags))
		svc_close_xprt(rqstp->rq_xprt);
	dprintk("svc: svc_process close\n");
	return 0;

err_short_len:
	svc_printk(rqstp, "short len %zd, dropping request\n",
			argv->iov_len);
	goto close;

err_bad_rpc:
	serv->sv_stats->rpcbadfmt++;
	svc_putnl(resv, 1);	/* REJECT */
	svc_putnl(resv, 0);	/* RPC_MISMATCH */
	svc_putnl(resv, 2);	/* Only RPCv2 supported */
	svc_putnl(resv, 2);
	goto sendit;

err_bad_auth:
	dprintk("svc: authentication failed (%d)\n", ntohl(auth_stat));
	serv->sv_stats->rpcbadauth++;
	/* Restore write pointer to location of accept status: */
	xdr_ressize_check(rqstp, reply_statp);
	svc_putnl(resv, 1);	/* REJECT */
	svc_putnl(resv, 1);	/* AUTH_ERROR */
	svc_putnl(resv, ntohl(auth_stat));	/* status */
	goto sendit;

err_bad_prog:
	dprintk("svc: unknown program %d\n", prog);
	serv->sv_stats->rpcbadfmt++;
	svc_putnl(resv, RPC_PROG_UNAVAIL);
	goto sendit;

err_bad_vers:
	svc_printk(rqstp, "unknown version (%d for prog %d, %s)\n",
		       vers, prog, progp->pg_name);

	serv->sv_stats->rpcbadfmt++;
	svc_putnl(resv, RPC_PROG_MISMATCH);
	svc_putnl(resv, progp->pg_lovers);
	svc_putnl(resv, progp->pg_hivers);
	goto sendit;

err_bad_proc:
	svc_printk(rqstp, "unknown procedure (%d)\n", proc);

	serv->sv_stats->rpcbadfmt++;
	svc_putnl(resv, RPC_PROC_UNAVAIL);
	goto sendit;

err_garbage:
	svc_printk(rqstp, "failed to decode args\n");

	rpc_stat = rpc_garbage_args;
err_bad:
	serv->sv_stats->rpcbadfmt++;
	svc_putnl(resv, ntohl(rpc_stat));
	goto sendit;
}
