static void get_timewait4_sock(struct inet_timewait_sock *tw,
			       struct seq_file *f, int i, int *len)
{
	__be32 dest, src;
	__u16 destp, srcp;
	int ttd = tw->tw_ttd - jiffies;

	if (ttd < 0)
		ttd = 0;

	dest  = tw->tw_daddr;
	src   = tw->tw_rcv_saddr;
	destp = ntohs(tw->tw_dport);
	srcp  = ntohs(tw->tw_sport);

	seq_printf(f, "%4d: %08X:%04X %08X:%04X"
		" %02X %08X:%08X %02X:%08lX %08X %5d %8d %d %d %p%n",
		i, src, srcp, dest, destp, tw->tw_substate, 0, 0,
		3, jiffies_to_clock_t(ttd), 0, 0, 0, 0,
		atomic_read(&tw->tw_refcnt), tw, len);
}
