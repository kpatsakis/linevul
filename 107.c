static int netlink_broadcast_deliver(struct sock *sk, struct sk_buff *skb)
{
	struct netlink_sock *nlk = nlk_sk(sk);

	if (atomic_read(&sk->sk_rmem_alloc) <= sk->sk_rcvbuf &&
	    !test_bit(0, &nlk->state)) {
		skb_set_owner_r(skb, sk);
		__netlink_sendskb(sk, skb);
		return atomic_read(&sk->sk_rmem_alloc) > (sk->sk_rcvbuf >> 1);
	}
	return -1;
}