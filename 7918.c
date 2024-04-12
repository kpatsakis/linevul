static void get_tcp6_sock(struct seq_file *seq, struct sock *sp, int i)
{
	const struct in6_addr *dest, *src;
	__u16 destp, srcp;
	int timer_active;
	unsigned long timer_expires;
	struct inet_sock *inet = inet_sk(sp);
	struct tcp_sock *tp = tcp_sk(sp);
	const struct inet_connection_sock *icsk = inet_csk(sp);
	struct ipv6_pinfo *np = inet6_sk(sp);

	dest  = &np->daddr;
	src   = &np->rcv_saddr;
	destp = ntohs(inet->inet_dport);
	srcp  = ntohs(inet->inet_sport);

	if (icsk->icsk_pending == ICSK_TIME_RETRANS) {
		timer_active	= 1;
		timer_expires	= icsk->icsk_timeout;
	} else if (icsk->icsk_pending == ICSK_TIME_PROBE0) {
		timer_active	= 4;
		timer_expires	= icsk->icsk_timeout;
	} else if (timer_pending(&sp->sk_timer)) {
		timer_active	= 2;
		timer_expires	= sp->sk_timer.expires;
	} else {
		timer_active	= 0;
		timer_expires = jiffies;
	}

	seq_printf(seq,
		   "%4d: %08X%08X%08X%08X:%04X %08X%08X%08X%08X:%04X "
		   "%02X %08X:%08X %02X:%08lX %08X %5d %8d %lu %d %pK %lu %lu %u %u %d\n",
		   i,
		   src->s6_addr32[0], src->s6_addr32[1],
		   src->s6_addr32[2], src->s6_addr32[3], srcp,
		   dest->s6_addr32[0], dest->s6_addr32[1],
		   dest->s6_addr32[2], dest->s6_addr32[3], destp,
		   sp->sk_state,
		   tp->write_seq-tp->snd_una,
		   (sp->sk_state == TCP_LISTEN) ? sp->sk_ack_backlog : (tp->rcv_nxt - tp->copied_seq),
		   timer_active,
		   jiffies_to_clock_t(timer_expires - jiffies),
		   icsk->icsk_retransmits,
		   sock_i_uid(sp),
		   icsk->icsk_probes_out,
		   sock_i_ino(sp),
		   atomic_read(&sp->sk_refcnt), sp,
		   jiffies_to_clock_t(icsk->icsk_rto),
		   jiffies_to_clock_t(icsk->icsk_ack.ato),
		   (icsk->icsk_ack.quick << 1 ) | icsk->icsk_ack.pingpong,
		   tp->snd_cwnd,
		   tcp_in_initial_slowstart(tp) ? -1 : tp->snd_ssthresh
		   );
}
