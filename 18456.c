static void l2cap_raw_recv(struct l2cap_conn *conn, struct sk_buff *skb)
{
	struct l2cap_chan_list *l = &conn->chan_list;
	struct sk_buff *nskb;
	struct sock *sk;

	BT_DBG("conn %p", conn);

	read_lock(&l->lock);
	for (sk = l->head; sk; sk = l2cap_pi(sk)->next_c) {
		if (sk->sk_type != SOCK_RAW)
			continue;

		/* Don't send frame to the socket it came from */
		if (skb->sk == sk)
			continue;
		nskb = skb_clone(skb, GFP_ATOMIC);
		if (!nskb)
			continue;

		if (sock_queue_rcv_skb(sk, nskb))
			kfree_skb(nskb);
	}
	read_unlock(&l->lock);
}
