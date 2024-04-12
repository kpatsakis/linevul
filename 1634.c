nfsd_inject_forget_client_openowners(struct sockaddr_storage *addr,
				     size_t addr_size)
{
	unsigned int count = 0;
	struct nfs4_client *clp;
	struct nfsd_net *nn = net_generic(current->nsproxy->net_ns,
						nfsd_net_id);
	LIST_HEAD(reaplist);

	if (!nfsd_netns_ready(nn))
		return count;

	spin_lock(&nn->client_lock);
	clp = nfsd_find_client(addr, addr_size);
	if (clp)
		count = nfsd_collect_client_openowners(clp, &reaplist, 0);
	spin_unlock(&nn->client_lock);
	nfsd_reap_openowners(&reaplist);
	return count;
}
