static struct nfsd4_conn *__nfsd4_find_conn(struct svc_xprt *xpt, struct nfsd4_session *s)
{
	struct nfsd4_conn *c;

	list_for_each_entry(c, &s->se_conns, cn_persession) {
		if (c->cn_xprt == xpt) {
			return c;
		}
	}
	return NULL;
}
