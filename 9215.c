static void l2cap_add_conf_opt(void **ptr, u8 type, u8 len, unsigned long val)
{
	struct l2cap_conf_opt *opt = *ptr;

	BT_DBG("type 0x%2.2x len %d val 0x%lx", type, len, val);

	opt->type = type;
	opt->len  = len;

	switch (len) {
	case 1:
		*((u8 *) opt->val)  = val;
		break;

	case 2:
		*((__le16 *) opt->val) = cpu_to_le16(val);
		break;

	case 4:
		*((__le32 *) opt->val) = cpu_to_le32(val);
		break;

	default:
		memcpy(opt->val, (void *) val, len);
		break;
	}

 	*ptr += L2CAP_CONF_OPT_SIZE + len;
 }
