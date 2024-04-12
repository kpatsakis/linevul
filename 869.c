static struct hlist_head *listen_hash(struct sockaddr_dn *addr)
{
	int i;
	unsigned int hash = addr->sdn_objnum;

	if (hash == 0) {
		hash = addr->sdn_objnamel;
		for(i = 0; i < le16_to_cpu(addr->sdn_objnamel); i++) {
			hash ^= addr->sdn_objname[i];
			hash ^= (hash << 3);
		}
	}

	return &dn_sk_hash[hash & DN_SK_HASH_MASK];
}
