static void age_mic_context(miccntx *cur, miccntx *old, u8 *key, int key_len,
			    struct crypto_cipher *tfm)
{
	/* If the current MIC context is valid and its key is the same as
	 * the MIC register, there's nothing to do.
	 */
	if (cur->valid && (memcmp(cur->key, key, key_len) == 0))
		return;

	/* Age current mic Context */
	memcpy(old, cur, sizeof(*cur));

	/* Initialize new context */
	memcpy(cur->key, key, key_len);
	cur->window  = 33; /* Window always points to the middle */
	cur->rx      = 0;  /* Rx Sequence numbers */
	cur->tx      = 0;  /* Tx sequence numbers */
	cur->valid   = 1;  /* Key is now valid */

	/* Give key to mic seed */
	emmh32_setseed(&cur->seed, key, key_len, tfm);
}
