static struct mr6_table *ip6mr_new_table(struct net *net, u32 id)
{
	struct mr6_table *mrt;
	unsigned int i;

	mrt = ip6mr_get_table(net, id);
	if (mrt)
		return mrt;

	mrt = kzalloc(sizeof(*mrt), GFP_KERNEL);
	if (!mrt)
		return NULL;
	mrt->id = id;
	write_pnet(&mrt->net, net);

	/* Forwarding cache */
	for (i = 0; i < MFC6_LINES; i++)
		INIT_LIST_HEAD(&mrt->mfc6_cache_array[i]);

	INIT_LIST_HEAD(&mrt->mfc6_unres_queue);

	setup_timer(&mrt->ipmr_expire_timer, ipmr_expire_process,
		    (unsigned long)mrt);

#ifdef CONFIG_IPV6_PIMSM_V2
	mrt->mroute_reg_vif_num = -1;
#endif
#ifdef CONFIG_IPV6_MROUTE_MULTIPLE_TABLES
	list_add_tail_rcu(&mrt->list, &net->ipv6.mr6_tables);
#endif
	return mrt;
}
