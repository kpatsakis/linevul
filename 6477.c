static int ipgre_header_parse(const struct sk_buff *skb, unsigned char *haddr)
{
	struct iphdr *iph = (struct iphdr *) skb_mac_header(skb);
	memcpy(haddr, &iph->saddr, 4);
	return 4;
}
