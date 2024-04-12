static void tcp_ecn_withdraw_cwr(struct tcp_sock *tp)
{
	tp->ecn_flags &= ~TCP_ECN_DEMAND_CWR;
}
