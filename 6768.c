static long keyring_read(const struct key *keyring,
			 char __user *buffer, size_t buflen)
{
	struct keyring_read_iterator_context ctx;
	unsigned long nr_keys;
	int ret;

	kenter("{%d},,%zu", key_serial(keyring), buflen);

	if (buflen & (sizeof(key_serial_t) - 1))
		return -EINVAL;

	nr_keys = keyring->keys.nr_leaves_on_tree;
	if (nr_keys == 0)
		return 0;

	/* Calculate how much data we could return */
	if (!buffer || !buflen)
		return nr_keys * sizeof(key_serial_t);

	/* Copy the IDs of the subscribed keys into the buffer */
	ctx.buffer = (key_serial_t __user *)buffer;
	ctx.buflen = buflen;
	ctx.count = 0;
	ret = assoc_array_iterate(&keyring->keys, keyring_read_iterator, &ctx);
	if (ret < 0) {
		kleave(" = %d [iterate]", ret);
		return ret;
	}

	kleave(" = %zu [ok]", ctx.count);
	return ctx.count;
}
