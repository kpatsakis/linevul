static bool decode_verify_name_request(void *mem_ctx, DATA_BLOB in, void *_out)
{
	void **out = (void **)_out;
	DATA_BLOB name;
	struct asn1_data *data = asn1_init(mem_ctx);
	struct ldb_verify_name_control *lvnc;
	int len;

	if (!data) return false;

	if (!asn1_load(data, in)) {
		return false;
	}

	lvnc = talloc(mem_ctx, struct ldb_verify_name_control);
	if (!lvnc) {
		return false;
	}

	if (!asn1_start_tag(data, ASN1_SEQUENCE(0))) {
		return false;
	}

	if (!asn1_read_Integer(data, &(lvnc->flags))) {
		return false;
	}

	if (!asn1_read_OctetString(data, mem_ctx, &name)) {
		return false;
	}

	if (name.length) {
		len = utf16_len_n(name.data, name.length);
		convert_string_talloc(mem_ctx, CH_UTF16, CH_UNIX,
					name.data, len,
					(void **)&lvnc->gc, &lvnc->gc_len);

		if (!(lvnc->gc)) {
			return false;
		}
	} else {
		lvnc->gc_len = 0;
		lvnc->gc = NULL;
	}

	if (!asn1_end_tag(data)) {
		return false;
	}

	*out = lvnc;
	return true;
}
