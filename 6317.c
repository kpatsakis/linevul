static bool ldap_encode_control(void *mem_ctx, struct asn1_data *data,
				const struct ldap_control_handler *handlers,
				struct ldb_control *ctrl)
{
	DATA_BLOB value;
	int i;

	if (!handlers) {
		return false;
	}

	for (i = 0; handlers[i].oid != NULL; i++) {
		if (!ctrl->oid) {
			/* not encoding this control, the OID has been
			 * set to NULL indicating it isn't really
			 * here */
			return true;
		}
		if (strcmp(handlers[i].oid, ctrl->oid) == 0) {
			if (!handlers[i].encode) {
				if (ctrl->critical) {
					return false;
				} else {
					/* not encoding this control */
					return true;
				}
			}
			if (!handlers[i].encode(mem_ctx, ctrl->data, &value)) {
				return false;
			}
			break;
		}
	}
	if (handlers[i].oid == NULL) {
		return false;
	}

	if (!asn1_push_tag(data, ASN1_SEQUENCE(0))) {
		return false;
	}

	if (!asn1_write_OctetString(data, ctrl->oid, strlen(ctrl->oid))) {
		return false;
	}

	if (ctrl->critical) {
		if (!asn1_write_BOOLEAN(data, ctrl->critical)) {
			return false;
		}
	}

	if (!ctrl->data) {
		goto pop_tag;
	}

	if (!asn1_write_OctetString(data, value.data, value.length)) {
		return false;
	}

pop_tag:
	if (!asn1_pop_tag(data)) {
		return false;
	}

	return true;
}
