default_opaque_binary_tag(tvbuff_t *tvb, guint32 offset,
			  guint8 token _U_, guint8 codepage _U_, guint32 *length)
{
	guint32 data_len = tvb_get_guintvar(tvb, offset, length);
	char *str = wmem_strdup_printf(wmem_packet_scope(), "(%d bytes of opaque data)", data_len);
	*length += data_len;
	return str;
}
