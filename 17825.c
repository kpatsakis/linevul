int keyring_clear(struct key *keyring)
{
	struct assoc_array_edit *edit;
	int ret;

	if (keyring->type != &key_type_keyring)
		return -ENOTDIR;

	down_write(&keyring->sem);

	edit = assoc_array_clear(&keyring->keys, &keyring_assoc_array_ops);
	if (IS_ERR(edit)) {
		ret = PTR_ERR(edit);
	} else {
		if (edit)
			assoc_array_apply_edit(edit);
		key_payload_reserve(keyring, 0);
		ret = 0;
	}

	up_write(&keyring->sem);
	return ret;
}
