static void encap_finish(void)
{
	hash_clean(encap_hash, (void (*)(void *))encap_free);
	hash_free(encap_hash);
	encap_hash = NULL;
#if ENABLE_BGP_VNC
	hash_clean(vnc_hash, (void (*)(void *))encap_free);
	hash_free(vnc_hash);
	vnc_hash = NULL;
#endif
}
