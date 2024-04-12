static void set_acl_from_sec_attr(sc_card_t *card, sc_file_t *file)
{
	unsigned int method;
	unsigned long key_ref;

	assert(card && card->ctx && file);
	assert(file->sec_attr  &&  file->sec_attr_len == SC_RTECP_SEC_ATTR_SIZE);
	assert(1 + 6 < SC_RTECP_SEC_ATTR_SIZE);

	sc_file_add_acl_entry(file, SC_AC_OP_SELECT, SC_AC_NONE, SC_AC_KEY_REF_NONE);
	if (file->sec_attr[0] & 0x40) /* if AccessMode.6 */
	{
		method = sec_attr_to_method(file->sec_attr[1 + 6]);
		key_ref = sec_attr_to_key_ref(file->sec_attr[1 + 6]);
		sc_debug(card->ctx, SC_LOG_DEBUG_NORMAL,
			"SC_AC_OP_DELETE %i %lu\n",
			(int)method, key_ref);
		sc_file_add_acl_entry(file, SC_AC_OP_DELETE, method, key_ref);
	}
	if (file->sec_attr[0] & 0x01) /* if AccessMode.0 */
	{
		method = sec_attr_to_method(file->sec_attr[1 + 0]);
		key_ref = sec_attr_to_key_ref(file->sec_attr[1 + 0]);
		sc_debug(card->ctx, SC_LOG_DEBUG_NORMAL,
			(file->type == SC_FILE_TYPE_DF) ?
				"SC_AC_OP_CREATE %i %lu\n"
				: "SC_AC_OP_READ %i %lu\n",
			(int)method, key_ref);
		sc_file_add_acl_entry(file, (file->type == SC_FILE_TYPE_DF) ?
				SC_AC_OP_CREATE : SC_AC_OP_READ, method, key_ref);
	}
	if (file->type == SC_FILE_TYPE_DF)
	{
		sc_file_add_acl_entry(file, SC_AC_OP_LIST_FILES,
				SC_AC_NONE, SC_AC_KEY_REF_NONE);
	}
	else
		if (file->sec_attr[0] & 0x02) /* if AccessMode.1 */
		{
			method = sec_attr_to_method(file->sec_attr[1 + 1]);
			key_ref = sec_attr_to_key_ref(file->sec_attr[1 + 1]);
			sc_debug(card->ctx, SC_LOG_DEBUG_NORMAL,
				"SC_AC_OP_UPDATE %i %lu\n",
				(int)method, key_ref);
			sc_file_add_acl_entry(file, SC_AC_OP_UPDATE, method, key_ref);
			sc_debug(card->ctx, SC_LOG_DEBUG_NORMAL,
				"SC_AC_OP_WRITE %i %lu\n",
				(int)method, key_ref);
			sc_file_add_acl_entry(file, SC_AC_OP_WRITE, method, key_ref);
		}
}
