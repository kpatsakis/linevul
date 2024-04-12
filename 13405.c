static void ipip6_tunnel_clone_6rd(struct net_device *dev, struct sit_net *sitn)
{
#ifdef CONFIG_IPV6_SIT_6RD
	struct ip_tunnel *t = netdev_priv(dev);

	if (t->dev == sitn->fb_tunnel_dev) {
		ipv6_addr_set(&t->ip6rd.prefix, htonl(0x20020000), 0, 0, 0);
		t->ip6rd.relay_prefix = 0;
		t->ip6rd.prefixlen = 16;
		t->ip6rd.relay_prefixlen = 0;
	} else {
		struct ip_tunnel *t0 = netdev_priv(sitn->fb_tunnel_dev);
		memcpy(&t->ip6rd, &t0->ip6rd, sizeof(t->ip6rd));
	}
#endif
}
