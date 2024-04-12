static bool ndp_msg_check_opts(struct ndp_msg *msg)
{
	unsigned char *ptr = ndp_msg_payload_opts(msg);
	size_t len = ndp_msg_payload_opts_len(msg);
	struct ndp_msg_opt_type_info *info;

	while (len > 0) {
		uint8_t cur_opt_raw_type = ptr[0];
		unsigned int cur_opt_len = ptr[1] << 3; /* convert to bytes */

		if (!cur_opt_len)
			return false;
		if (len < cur_opt_len)
			break;
		info = ndp_msg_opt_type_info_by_raw_type(cur_opt_raw_type);
		if (info) {
			if (cur_opt_len < info->raw_struct_size ||
			    (info->check_valid && !info->check_valid(ptr)))
				ptr[0] = __INVALID_OPT_TYPE_MAGIC;
		}
		ptr += cur_opt_len;
		len -= cur_opt_len;
	}

	return true;
}
