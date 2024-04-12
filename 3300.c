pseudo_set_job_attr( const char *name, const char *expr, bool log )
{
	RemoteResource *remote;
	if (parallelMasterResource == NULL) {
		remote = thisRemoteResource;
	} else {
		remote = parallelMasterResource;
	}
	if(Shadow->updateJobAttr(name,expr,log)) {
		dprintf(D_SYSCALLS,"pseudo_set_job_attr(%s,%s) succeeded\n",name,expr);
		ClassAd *ad = remote->getJobAd();
		ASSERT(ad);
		ad->AssignExpr(name,expr);
		return 0;
	} else {
		dprintf(D_SYSCALLS,"pseudo_set_job_attr(%s,%s) failed\n",name,expr);
		return -1;
	}
}
