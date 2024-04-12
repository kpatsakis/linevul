static void ct_build_clabel(const struct nf_conntrack *ct, struct nethdr *n)
{
	const struct nfct_bitmask *b;
	uint32_t *words;
	unsigned int wordcount, i, maxbit;

	if (!nfct_attr_is_set(ct, ATTR_CONNLABELS))
		return;

	b = nfct_get_attr(ct, ATTR_CONNLABELS);

	maxbit = nfct_bitmask_maxbit(b);
	for (i=0; i <= maxbit; i++) {
		if (nfct_bitmask_test_bit(b, i))
			break;
	}

	if (i > maxbit)
		return;

	wordcount = (nfct_bitmask_maxbit(b) / 32) + 1;
	words = put_header(n, NTA_LABELS, wordcount * sizeof(*words));

	for (i=0; i < wordcount; i++) {
		int bit = 31;
		uint32_t tmp = 0;

		do {
			if (nfct_bitmask_test_bit(b, (32 * i) + bit))
				tmp |= (1 << bit);
		} while (--bit >= 0);

		words[i] = htonl(tmp);
	}
}
