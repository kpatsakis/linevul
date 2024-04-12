static inline int cookie_check(struct sk_buff *skb, __u32 cookie)
{
	const struct iphdr *iph = ip_hdr(skb);
	const struct tcphdr *th = tcp_hdr(skb);
	__u32 seq = ntohl(th->seq) - 1;
	__u32 mssind = check_tcp_syn_cookie(cookie, iph->saddr, iph->daddr,
					    th->source, th->dest, seq,
					    jiffies / (HZ * 60),
					    COUNTER_TRIES);

	return mssind < ARRAY_SIZE(msstab) ? msstab[mssind] : 0;
}
