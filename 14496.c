void *tcp_v4_tw_get_peer(struct sock *sk)
{
	struct inet_timewait_sock *tw = inet_twsk(sk);

	return inet_getpeer_v4(tw->tw_daddr, 1);
}
