static int udf_CS0toNLS(struct nls_table *nls, struct ustr *utf_o,
			const struct ustr *ocu_i)
{
	const uint8_t *ocu;
	uint8_t cmp_id, ocu_len;
	int i, len;


	ocu_len = ocu_i->u_len;
	if (ocu_len == 0) {
		memset(utf_o, 0, sizeof(struct ustr));
		return 0;
	}

	cmp_id = ocu_i->u_cmpID;
	if (cmp_id != 8 && cmp_id != 16) {
		memset(utf_o, 0, sizeof(struct ustr));
		pr_err("unknown compression code (%d) stri=%s\n",
		       cmp_id, ocu_i->u_name);
		return 0;
	}

	ocu = ocu_i->u_name;
	utf_o->u_len = 0;
	for (i = 0; (i < ocu_len) && (utf_o->u_len <= (UDF_NAME_LEN - 3));) {
		/* Expand OSTA compressed Unicode to Unicode */
		uint32_t c = ocu[i++];
		if (cmp_id == 16)
			c = (c << 8) | ocu[i++];

		len = nls->uni2char(c, &utf_o->u_name[utf_o->u_len],
				    UDF_NAME_LEN - utf_o->u_len);
		/* Valid character? */
		if (len >= 0)
			utf_o->u_len += len;
		else
			utf_o->u_name[utf_o->u_len++] = '?';
	}
	utf_o->u_cmpID = 8;

	return utf_o->u_len;
}
