static int dn_accept(struct socket *sock, struct socket *newsock, int flags)
{
	struct sock *sk = sock->sk, *newsk;
	struct sk_buff *skb = NULL;
	struct dn_skb_cb *cb;
	unsigned char menuver;
	int err = 0;
	unsigned char type;
	long timeo = sock_rcvtimeo(sk, flags & O_NONBLOCK);
	struct dst_entry *dst;

	lock_sock(sk);

	if (sk->sk_state != TCP_LISTEN || DN_SK(sk)->state != DN_O) {
		release_sock(sk);
		return -EINVAL;
	}

	skb = skb_dequeue(&sk->sk_receive_queue);
	if (skb == NULL) {
		skb = dn_wait_for_connect(sk, &timeo);
		if (IS_ERR(skb)) {
			release_sock(sk);
			return PTR_ERR(skb);
		}
	}

	cb = DN_SKB_CB(skb);
	sk->sk_ack_backlog--;
	newsk = dn_alloc_sock(sock_net(sk), newsock, sk->sk_allocation, 0);
	if (newsk == NULL) {
		release_sock(sk);
		kfree_skb(skb);
		return -ENOBUFS;
	}
	release_sock(sk);

	dst = skb_dst(skb);
	sk_dst_set(newsk, dst);
	skb_dst_set(skb, NULL);

	DN_SK(newsk)->state        = DN_CR;
	DN_SK(newsk)->addrrem      = cb->src_port;
	DN_SK(newsk)->services_rem = cb->services;
	DN_SK(newsk)->info_rem     = cb->info;
	DN_SK(newsk)->segsize_rem  = cb->segsize;
	DN_SK(newsk)->accept_mode  = DN_SK(sk)->accept_mode;

	if (DN_SK(newsk)->segsize_rem < 230)
		DN_SK(newsk)->segsize_rem = 230;

	if ((DN_SK(newsk)->services_rem & NSP_FC_MASK) == NSP_FC_NONE)
		DN_SK(newsk)->max_window = decnet_no_fc_max_cwnd;

	newsk->sk_state  = TCP_LISTEN;
	memcpy(&(DN_SK(newsk)->addr), &(DN_SK(sk)->addr), sizeof(struct sockaddr_dn));

	/*
	 * If we are listening on a wild socket, we don't want
	 * the newly created socket on the wrong hash queue.
	 */
	DN_SK(newsk)->addr.sdn_flags &= ~SDF_WILD;

	skb_pull(skb, dn_username2sockaddr(skb->data, skb->len, &(DN_SK(newsk)->addr), &type));
	skb_pull(skb, dn_username2sockaddr(skb->data, skb->len, &(DN_SK(newsk)->peer), &type));
	*(__le16 *)(DN_SK(newsk)->peer.sdn_add.a_addr) = cb->src;
	*(__le16 *)(DN_SK(newsk)->addr.sdn_add.a_addr) = cb->dst;

	menuver = *skb->data;
	skb_pull(skb, 1);

	if (menuver & DN_MENUVER_ACC)
		dn_access_copy(skb, &(DN_SK(newsk)->accessdata));

	if (menuver & DN_MENUVER_USR)
		dn_user_copy(skb, &(DN_SK(newsk)->conndata_in));

	if (menuver & DN_MENUVER_PRX)
		DN_SK(newsk)->peer.sdn_flags |= SDF_PROXY;

	if (menuver & DN_MENUVER_UIC)
		DN_SK(newsk)->peer.sdn_flags |= SDF_UICPROXY;

	kfree_skb(skb);

	memcpy(&(DN_SK(newsk)->conndata_out), &(DN_SK(sk)->conndata_out),
		sizeof(struct optdata_dn));
	memcpy(&(DN_SK(newsk)->discdata_out), &(DN_SK(sk)->discdata_out),
		sizeof(struct optdata_dn));

	lock_sock(newsk);
	err = dn_hash_sock(newsk);
	if (err == 0) {
		sock_reset_flag(newsk, SOCK_ZAPPED);
		dn_send_conn_ack(newsk);

		/*
		 * Here we use sk->sk_allocation since although the conn conf is
		 * for the newsk, the context is the old socket.
		 */
		if (DN_SK(newsk)->accept_mode == ACC_IMMED)
			err = dn_confirm_accept(newsk, &timeo,
						sk->sk_allocation);
	}
	release_sock(newsk);
	return err;
}
