static int __net_init icmp_sk_init(struct net *net)
{
	int i, err;

	net->ipv4.icmp_sk =
		kzalloc(nr_cpu_ids * sizeof(struct sock *), GFP_KERNEL);
	if (net->ipv4.icmp_sk == NULL)
		return -ENOMEM;

	for_each_possible_cpu(i) {
		struct sock *sk;

		err = inet_ctl_sock_create(&sk, PF_INET,
					   SOCK_RAW, IPPROTO_ICMP, net);
		if (err < 0)
			goto fail;

		net->ipv4.icmp_sk[i] = sk;

		/* Enough space for 2 64K ICMP packets, including
		 * sk_buff struct overhead.
		 */
		sk->sk_sndbuf =
			(2 * ((64 * 1024) + sizeof(struct sk_buff)));

		/*
		 * Speedup sock_wfree()
		 */
		sock_set_flag(sk, SOCK_USE_WRITE_QUEUE);
		inet_sk(sk)->pmtudisc = IP_PMTUDISC_DONT;
	}

	/* Control parameters for ECHO replies. */
	net->ipv4.sysctl_icmp_echo_ignore_all = 0;
	net->ipv4.sysctl_icmp_echo_ignore_broadcasts = 1;

	/* Control parameter - ignore bogus broadcast responses? */
	net->ipv4.sysctl_icmp_ignore_bogus_error_responses = 1;

	/*
	 * 	Configurable global rate limit.
	 *
	 *	ratelimit defines tokens/packet consumed for dst->rate_token
	 *	bucket ratemask defines which icmp types are ratelimited by
	 *	setting	it's bit position.
	 *
	 *	default:
	 *	dest unreachable (3), source quench (4),
	 *	time exceeded (11), parameter problem (12)
	 */

	net->ipv4.sysctl_icmp_ratelimit = 1 * HZ;
	net->ipv4.sysctl_icmp_ratemask = 0x1818;
	net->ipv4.sysctl_icmp_errors_use_inbound_ifaddr = 0;

	return 0;

fail:
	for_each_possible_cpu(i)
		inet_ctl_sock_destroy(net->ipv4.icmp_sk[i]);
	kfree(net->ipv4.icmp_sk);
	return err;
}
