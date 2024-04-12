static int netlink_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct netlink_sock *nlk;

	if (!sk)
		return 0;

	netlink_remove(sk);
	sock_orphan(sk);
	nlk = nlk_sk(sk);

	/*
	 * OK. Socket is unlinked, any packets that arrive now
	 * will be purged.
	 */

	sock->sk = NULL;
	wake_up_interruptible_all(&nlk->wait);

	skb_queue_purge(&sk->sk_write_queue);

	if (nlk->portid) {
		struct netlink_notify n = {
						.net = sock_net(sk),
						.protocol = sk->sk_protocol,
						.portid = nlk->portid,
					  };
		atomic_notifier_call_chain(&netlink_chain,
				NETLINK_URELEASE, &n);
	}

	module_put(nlk->module);

	netlink_table_grab();
	if (netlink_is_kernel(sk)) {
		BUG_ON(nl_table[sk->sk_protocol].registered == 0);
		if (--nl_table[sk->sk_protocol].registered == 0) {
			struct listeners *old;

			old = nl_deref_protected(nl_table[sk->sk_protocol].listeners);
			RCU_INIT_POINTER(nl_table[sk->sk_protocol].listeners, NULL);
			kfree_rcu(old, rcu);
			nl_table[sk->sk_protocol].module = NULL;
			nl_table[sk->sk_protocol].bind = NULL;
			nl_table[sk->sk_protocol].flags = 0;
			nl_table[sk->sk_protocol].registered = 0;
		}
	} else if (nlk->subscriptions) {
		netlink_update_listeners(sk);
	}
	netlink_table_ungrab();

	kfree(nlk->groups);
	nlk->groups = NULL;

	local_bh_disable();
	sock_prot_inuse_add(sock_net(sk), &netlink_proto, -1);
	local_bh_enable();
	sock_put(sk);
	return 0;
}
