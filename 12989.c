kex_free_newkeys(struct newkeys *newkeys)
{
	if (newkeys == NULL)
		return;
	if (newkeys->enc.key) {
		explicit_bzero(newkeys->enc.key, newkeys->enc.key_len);
		free(newkeys->enc.key);
		newkeys->enc.key = NULL;
	}
	if (newkeys->enc.iv) {
		explicit_bzero(newkeys->enc.iv, newkeys->enc.iv_len);
		free(newkeys->enc.iv);
		newkeys->enc.iv = NULL;
	}
	free(newkeys->enc.name);
	explicit_bzero(&newkeys->enc, sizeof(newkeys->enc));
	free(newkeys->comp.name);
	explicit_bzero(&newkeys->comp, sizeof(newkeys->comp));
	mac_clear(&newkeys->mac);
	if (newkeys->mac.key) {
		explicit_bzero(newkeys->mac.key, newkeys->mac.key_len);
		free(newkeys->mac.key);
		newkeys->mac.key = NULL;
	}
	free(newkeys->mac.name);
	explicit_bzero(&newkeys->mac, sizeof(newkeys->mac));
	explicit_bzero(newkeys, sizeof(*newkeys));
	free(newkeys);
}
