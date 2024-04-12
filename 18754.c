check_gss_callback_principal(struct nfs_client *clp, struct svc_rqst *rqstp)
{
	char *p = rqstp->rq_cred.cr_principal;

	if (rqstp->rq_authop->flavour != RPC_AUTH_GSS)
		return 1;

	/* No RPC_AUTH_GSS on NFSv4.1 back channel yet */
	if (clp->cl_minorversion != 0)
		return 0;
	/*
	 * It might just be a normal user principal, in which case
	 * userspace won't bother to tell us the name at all.
	 */
	if (p == NULL)
		return 0;

	/*
	 * Did we get the acceptor from userland during the SETCLIENID
	 * negotiation?
	 */
	if (clp->cl_acceptor)
		return !strcmp(p, clp->cl_acceptor);

	/*
	 * Otherwise try to verify it using the cl_hostname. Note that this
	 * doesn't work if a non-canonical hostname was used in the devname.
	 */

	/* Expect a GSS_C_NT_HOSTBASED_NAME like "nfs@serverhostname" */

	if (memcmp(p, "nfs@", 4) != 0)
		return 0;
	p += 4;
	if (strcmp(p, clp->cl_hostname) != 0)
		return 0;
	return 1;
}
