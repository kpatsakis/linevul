static void *ip6mr_vif_seq_next(struct seq_file *seq, void *v, loff_t *pos)
{
	struct ipmr_vif_iter *iter = seq->private;
	struct net *net = seq_file_net(seq);
	struct mr6_table *mrt = iter->mrt;

	++*pos;
	if (v == SEQ_START_TOKEN)
		return ip6mr_vif_seq_idx(net, iter, 0);

	while (++iter->ct < mrt->maxvif) {
		if (!MIF_EXISTS(mrt, iter->ct))
			continue;
		return &mrt->vif6_table[iter->ct];
	}
	return NULL;
}
