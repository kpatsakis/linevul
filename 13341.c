static void nf_ct_frag6_evictor(void)
{
	local_bh_disable();
	inet_frag_evictor(&nf_init_frags, &nf_frags);
	local_bh_enable();
}
