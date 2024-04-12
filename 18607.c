static void get_timewait6_sock(struct seq_file *seq,
			       struct inet_timewait_sock *tw, int i)
{
	const struct in6_addr *dest, *src;
	__u16 destp, srcp;
	struct inet6_timewait_sock *tw6 = inet6_twsk((struct sock *)tw);
	int ttd = tw->tw_ttd - jiffies;

	if (ttd < 0)
		ttd = 0;

	dest = &tw6->tw_v6_daddr;
	src  = &tw6->tw_v6_rcv_saddr;
	destp = ntohs(tw->tw_dport);
	srcp  = ntohs(tw->tw_sport);

	seq_printf(seq,
		   "%4d: %08X%08X%08X%08X:%04X %08X%08X%08X%08X:%04X "
		   "%02X %08X:%08X %02X:%08lX %08X %5d %8d %d %d %pK\n",
		   i,
		   src->s6_addr32[0], src->s6_addr32[1],
		   src->s6_addr32[2], src->s6_addr32[3], srcp,
		   dest->s6_addr32[0], dest->s6_addr32[1],
		   dest->s6_addr32[2], dest->s6_addr32[3], destp,
		   tw->tw_substate, 0, 0,
		   3, jiffies_to_clock_t(ttd), 0, 0, 0, 0,
		   atomic_read(&tw->tw_refcnt), tw);
}
