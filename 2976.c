static inline u64 dccp_v4_init_sequence(const struct sk_buff *skb)
{
	return secure_dccp_sequence_number(ip_hdr(skb)->daddr,
					   ip_hdr(skb)->saddr,
					   dccp_hdr(skb)->dccph_dport,
					   dccp_hdr(skb)->dccph_sport);
}
