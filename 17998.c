static bool ldap_decode_control_wrapper(void *mem_ctx, struct asn1_data *data,
					struct ldb_control *ctrl, DATA_BLOB *value)
{
	DATA_BLOB oid;

	if (!asn1_start_tag(data, ASN1_SEQUENCE(0))) {
		return false;
	}

	if (!asn1_read_OctetString(data, mem_ctx, &oid)) {
		return false;
	}
	ctrl->oid = talloc_strndup(mem_ctx, (char *)oid.data, oid.length);
	if (!ctrl->oid) {
		return false;
	}

	if (asn1_peek_tag(data, ASN1_BOOLEAN)) {
		bool critical;
		if (!asn1_read_BOOLEAN(data, &critical)) {
			return false;
		}
		ctrl->critical = critical;
	} else {
		ctrl->critical = false;
	}

	ctrl->data = NULL;

	if (!asn1_peek_tag(data, ASN1_OCTET_STRING)) {
		*value = data_blob(NULL, 0);
		goto end_tag;
	}

	if (!asn1_read_OctetString(data, mem_ctx, value)) {
		return false;
	}

end_tag:
	if (!asn1_end_tag(data)) {
		return false;
	}

	return true;
}
