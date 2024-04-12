svc_rqst_free(struct svc_rqst *rqstp)
{
	svc_release_buffer(rqstp);
	kfree(rqstp->rq_resp);
	kfree(rqstp->rq_argp);
	kfree(rqstp->rq_auth_data);
	kfree_rcu(rqstp, rq_rcu_head);
}
