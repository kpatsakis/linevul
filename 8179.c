static void get_openreq6(struct seq_file *seq,
			 struct sock *sk, struct request_sock *req, int i, int uid)
{
	int ttd = req->expires - jiffies;
	const struct in6_addr *src = &inet6_rsk(req)->loc_addr;
	const struct in6_addr *dest = &inet6_rsk(req)->rmt_addr;

	if (ttd < 0)
		ttd = 0;

	seq_printf(seq,
		   "%4d: %08X%08X%08X%08X:%04X %08X%08X%08X%08X:%04X "
		   "%02X %08X:%08X %02X:%08lX %08X %5d %8d %d %d %p\n",
		   i,
		   src->s6_addr32[0], src->s6_addr32[1],
		   src->s6_addr32[2], src->s6_addr32[3],
		   ntohs(inet_rsk(req)->loc_port),
		   dest->s6_addr32[0], dest->s6_addr32[1],
		   dest->s6_addr32[2], dest->s6_addr32[3],
		   ntohs(inet_rsk(req)->rmt_port),
		   TCP_SYN_RECV,
		   0,0, /* could print option size, but that is af dependent. */
		   1,   /* timers active (only the expire timer) */
		   jiffies_to_clock_t(ttd),
		   req->retrans,
		   uid,
		   0,  /* non standard timer */
		   0, /* open_requests have no inode */
		   0, req);
}
