static int pppol2tp_xmit(struct ppp_channel *chan, struct sk_buff *skb)
{
	static const u8 ppph[2] = { 0xff, 0x03 };
	struct sock *sk = (struct sock *) chan->private;
	struct sock *sk_tun;
	struct l2tp_session *session;
	struct l2tp_tunnel *tunnel;
	struct pppol2tp_session *ps;
	int uhlen, headroom;

	if (sock_flag(sk, SOCK_DEAD) || !(sk->sk_state & PPPOX_CONNECTED))
		goto abort;

	/* Get session and tunnel contexts from the socket */
	session = pppol2tp_sock_to_session(sk);
	if (session == NULL)
		goto abort;

	ps = l2tp_session_priv(session);
	sk_tun = ps->tunnel_sock;
	if (sk_tun == NULL)
		goto abort_put_sess;
	tunnel = l2tp_sock_to_tunnel(sk_tun);
	if (tunnel == NULL)
		goto abort_put_sess;

	uhlen = (tunnel->encap == L2TP_ENCAPTYPE_UDP) ? sizeof(struct udphdr) : 0;
	headroom = NET_SKB_PAD +
		   sizeof(struct iphdr) + /* IP header */
		   uhlen +		/* UDP header (if L2TP_ENCAPTYPE_UDP) */
		   session->hdr_len +	/* L2TP header */
		   sizeof(ppph);	/* PPP header */
	if (skb_cow_head(skb, headroom))
		goto abort_put_sess_tun;

	/* Setup PPP header */
	__skb_push(skb, sizeof(ppph));
	skb->data[0] = ppph[0];
	skb->data[1] = ppph[1];

	local_bh_disable();
	l2tp_xmit_skb(session, skb, session->hdr_len);
	local_bh_enable();

	sock_put(sk_tun);
	sock_put(sk);
	return 1;

abort_put_sess_tun:
	sock_put(sk_tun);
abort_put_sess:
	sock_put(sk);
abort:
	/* Free the original skb */
	kfree_skb(skb);
	return 1;
}
