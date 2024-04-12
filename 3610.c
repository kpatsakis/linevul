static int l2tp_ip_bind(struct sock *sk, struct sockaddr *uaddr, int addr_len)
{
	struct inet_sock *inet = inet_sk(sk);
	struct sockaddr_l2tpip *addr = (struct sockaddr_l2tpip *) uaddr;
	int ret = -EINVAL;
	int chk_addr_ret;

	ret = -EADDRINUSE;
	read_lock_bh(&l2tp_ip_lock);
	if (__l2tp_ip_bind_lookup(&init_net, addr->l2tp_addr.s_addr, sk->sk_bound_dev_if, addr->l2tp_conn_id))
		goto out_in_use;

	read_unlock_bh(&l2tp_ip_lock);

	lock_sock(sk);
	if (sk->sk_state != TCP_CLOSE || addr_len < sizeof(struct sockaddr_l2tpip))
		goto out;

	chk_addr_ret = inet_addr_type(&init_net, addr->l2tp_addr.s_addr);
	ret = -EADDRNOTAVAIL;
	if (addr->l2tp_addr.s_addr && chk_addr_ret != RTN_LOCAL &&
	    chk_addr_ret != RTN_MULTICAST && chk_addr_ret != RTN_BROADCAST)
		goto out;

	inet->inet_rcv_saddr = inet->inet_saddr = addr->l2tp_addr.s_addr;
	if (chk_addr_ret == RTN_MULTICAST || chk_addr_ret == RTN_BROADCAST)
		inet->inet_saddr = 0;  /* Use device */
	sk_dst_reset(sk);

	l2tp_ip_sk(sk)->conn_id = addr->l2tp_conn_id;

	write_lock_bh(&l2tp_ip_lock);
	sk_add_bind_node(sk, &l2tp_ip_bind_table);
	sk_del_node_init(sk);
	write_unlock_bh(&l2tp_ip_lock);
	ret = 0;
out:
	release_sock(sk);

	return ret;

out_in_use:
	read_unlock_bh(&l2tp_ip_lock);

	return ret;
}
