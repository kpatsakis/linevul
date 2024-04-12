int nf_ct_frag6_init(void)
{
	nf_frags.hashfn = nf_hashfn;
	nf_frags.constructor = ip6_frag_init;
	nf_frags.destructor = NULL;
	nf_frags.skb_free = nf_skb_free;
	nf_frags.qsize = sizeof(struct nf_ct_frag6_queue);
	nf_frags.match = ip6_frag_match;
	nf_frags.frag_expire = nf_ct_frag6_expire;
	nf_frags.secret_interval = 10 * 60 * HZ;
	nf_init_frags.timeout = IPV6_FRAG_TIMEOUT;
	nf_init_frags.high_thresh = IPV6_FRAG_HIGH_THRESH;
	nf_init_frags.low_thresh = IPV6_FRAG_LOW_THRESH;
	inet_frags_init_net(&nf_init_frags);
	inet_frags_init(&nf_frags);

	return 0;
}
