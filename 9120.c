static int ipmr_mfc_seq_show(struct seq_file *seq, void *v)
{
	int n;

	if (v == SEQ_START_TOKEN) {
		seq_puts(seq,
			 "Group                            "
			 "Origin                           "
			 "Iif      Pkts  Bytes     Wrong  Oifs\n");
	} else {
		const struct mfc6_cache *mfc = v;
		const struct ipmr_mfc_iter *it = seq->private;
		struct mr6_table *mrt = it->mrt;

		seq_printf(seq, "%pI6 %pI6 %-3hd",
			   &mfc->mf6c_mcastgrp, &mfc->mf6c_origin,
			   mfc->mf6c_parent);

		if (it->cache != &mrt->mfc6_unres_queue) {
			seq_printf(seq, " %8lu %8lu %8lu",
				   mfc->mfc_un.res.pkt,
				   mfc->mfc_un.res.bytes,
				   mfc->mfc_un.res.wrong_if);
			for (n = mfc->mfc_un.res.minvif;
			     n < mfc->mfc_un.res.maxvif; n++) {
				if (MIF_EXISTS(mrt, n) &&
				    mfc->mfc_un.res.ttls[n] < 255)
					seq_printf(seq,
						   " %2d:%-3d",
						   n, mfc->mfc_un.res.ttls[n]);
			}
		} else {
			/* unresolved mfc_caches don't contain
			 * pkt, bytes and wrong_if values
			 */
			seq_printf(seq, " %8lu %8lu %8lu", 0ul, 0ul, 0ul);
		}
		seq_putc(seq, '\n');
	}
	return 0;
}
