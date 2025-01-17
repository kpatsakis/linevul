int svc_rdma_recvfrom(struct svc_rqst *rqstp)
{
struct svc_xprt *xprt = rqstp->rq_xprt;
struct svcxprt_rdma *rdma_xprt =
container_of(xprt, struct svcxprt_rdma, sc_xprt);
struct svc_rdma_op_ctxt *ctxt = NULL;
struct rpcrdma_msg *rmsgp;
int ret = 0;

dprintk("svcrdma: rqstp=%p\n", rqstp);

spin_lock(&rdma_xprt->sc_rq_dto_lock);
if (!list_empty(&rdma_xprt->sc_read_complete_q)) {
ctxt = list_first_entry(&rdma_xprt->sc_read_complete_q,
struct svc_rdma_op_ctxt, list);
list_del(&ctxt->list);
spin_unlock(&rdma_xprt->sc_rq_dto_lock);
rdma_read_complete(rqstp, ctxt);
goto complete;
} else if (!list_empty(&rdma_xprt->sc_rq_dto_q)) {
ctxt = list_first_entry(&rdma_xprt->sc_rq_dto_q,
struct svc_rdma_op_ctxt, list);
list_del(&ctxt->list);
} else {
atomic_inc(&rdma_stat_rq_starve);
clear_bit(XPT_DATA, &xprt->xpt_flags);
ctxt = NULL;
}
spin_unlock(&rdma_xprt->sc_rq_dto_lock);
if (!ctxt) {
/* This is the EAGAIN path. The svc_recv routine will
* return -EAGAIN, the nfsd thread will go to call into
* svc_recv again and we shouldn't be on the active
* transport list
*/
if (test_bit(XPT_CLOSE, &xprt->xpt_flags))
goto defer;
goto out;
}
dprintk("svcrdma: processing ctxt=%p on xprt=%p, rqstp=%p\n",
ctxt, rdma_xprt, rqstp);
atomic_inc(&rdma_stat_recv);

/* Build up the XDR from the receive buffers. */
rdma_build_arg_xdr(rqstp, ctxt, ctxt->byte_len);

/* Decode the RDMA header. */
rmsgp = (struct rpcrdma_msg *)rqstp->rq_arg.head[0].iov_base;
ret = svc_rdma_xdr_decode_req(&rqstp->rq_arg);
if (ret < 0)
goto out_err;
if (ret == 0)
goto out_drop;
rqstp->rq_xprt_hlen = ret;

	if (svc_rdma_is_backchannel_reply(xprt, rmsgp)) {
		ret = svc_rdma_handle_bc_reply(xprt->xpt_bc_xprt, rmsgp,
&rqstp->rq_arg);
svc_rdma_put_context(ctxt, 0);
if (ret)
goto repost;
return ret;
}

/* Read read-list data. */
ret = rdma_read_chunks(rdma_xprt, rmsgp, rqstp, ctxt);
if (ret > 0) {
/* read-list posted, defer until data received from client. */
goto defer;
} else if (ret < 0) {
/* Post of read-list failed, free context. */
svc_rdma_put_context(ctxt, 1);
return 0;
}

complete:
ret = rqstp->rq_arg.head[0].iov_len
+ rqstp->rq_arg.page_len
+ rqstp->rq_arg.tail[0].iov_len;
svc_rdma_put_context(ctxt, 0);
out:
dprintk("svcrdma: ret=%d, rq_arg.len=%u, "
"rq_arg.head[0].iov_base=%p, rq_arg.head[0].iov_len=%zd\n",
ret, rqstp->rq_arg.len,
rqstp->rq_arg.head[0].iov_base,
rqstp->rq_arg.head[0].iov_len);
rqstp->rq_prot = IPPROTO_MAX;
svc_xprt_copy_addrs(rqstp, xprt);
return ret;

out_err:
	svc_rdma_send_error(rdma_xprt, rmsgp, ret);
svc_rdma_put_context(ctxt, 0);
return 0;

defer:
return 0;

out_drop:
svc_rdma_put_context(ctxt, 1);
repost:
return svc_rdma_repost_recv(rdma_xprt, GFP_KERNEL);
}
