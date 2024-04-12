static int snmp6_alloc_dev(struct inet6_dev *idev)
{
	int i;

	idev->stats.ipv6 = alloc_percpu(struct ipstats_mib);
	if (!idev->stats.ipv6)
		goto err_ip;

	for_each_possible_cpu(i) {
		struct ipstats_mib *addrconf_stats;
		addrconf_stats = per_cpu_ptr(idev->stats.ipv6, i);
		u64_stats_init(&addrconf_stats->syncp);
	}


	idev->stats.icmpv6dev = kzalloc(sizeof(struct icmpv6_mib_device),
					GFP_KERNEL);
	if (!idev->stats.icmpv6dev)
		goto err_icmp;
	idev->stats.icmpv6msgdev = kzalloc(sizeof(struct icmpv6msg_mib_device),
					   GFP_KERNEL);
	if (!idev->stats.icmpv6msgdev)
		goto err_icmpmsg;

	return 0;

err_icmpmsg:
	kfree(idev->stats.icmpv6dev);
err_icmp:
	free_percpu(idev->stats.ipv6);
err_ip:
	return -ENOMEM;
}
