static bool svc_rqst_integrity_protected(struct svc_rqst *rqstp)
{
	struct svc_cred *cr = &rqstp->rq_cred;
	u32 service;

	if (!cr->cr_gss_mech)
		return false;
	service = gss_pseudoflavor_to_service(cr->cr_gss_mech, cr->cr_flavor);
	return service == RPC_GSS_SVC_INTEGRITY ||
	       service == RPC_GSS_SVC_PRIVACY;
}
