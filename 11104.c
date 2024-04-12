wv_integer_from_opaque(tvbuff_t *tvb, guint32 offset, guint32 data_len)
{
	char *str;

	switch (data_len) {
	case 1:
		str = wmem_strdup_printf(wmem_packet_scope(), "WV-CSP Integer: %d",
				      tvb_get_guint8(tvb, offset));
		break;
	case 2:
		str = wmem_strdup_printf(wmem_packet_scope(), "WV-CSP Integer: %d",
				      tvb_get_ntohs(tvb, offset));
		break;
	case 3:
		str = wmem_strdup_printf(wmem_packet_scope(), "WV-CSP Integer: %d",
				      tvb_get_ntoh24(tvb, offset));
		break;
	case 4:
		str = wmem_strdup_printf(wmem_packet_scope(), "WV-CSP Integer: %d",
				      tvb_get_ntohl(tvb, offset));
		break;
	default:
		str = wmem_strdup_printf(wmem_packet_scope(), "<Error: invalid binary WV-CSP Integer value "
				      "(%d bytes of opaque data)>", data_len);
		break;
	}

	return str;
}
