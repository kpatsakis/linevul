	__acquires(mrt_lock)
{
	struct ipmr_vif_iter *iter = seq->private;
	struct net *net = seq_file_net(seq);
	struct mr6_table *mrt;

	mrt = ip6mr_get_table(net, RT6_TABLE_DFLT);
	if (!mrt)
		return ERR_PTR(-ENOENT);

	iter->mrt = mrt;

	read_lock(&mrt_lock);
	return *pos ? ip6mr_vif_seq_idx(net, seq->private, *pos - 1)
		: SEQ_START_TOKEN;
}
