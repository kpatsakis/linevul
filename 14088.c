static int bond_xmit_hash_policy_l2(struct sk_buff *skb, int count)
{
	struct ethhdr *data = (struct ethhdr *)skb->data;

	return (data->h_dest[5] ^ data->h_source[5]) % count;
}
