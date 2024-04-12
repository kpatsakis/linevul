static unsigned int encap_hash_key_make(void *p)
{
	const struct bgp_attr_encap_subtlv *encap = p;

	return jhash(encap->value, encap->length, 0);
}
