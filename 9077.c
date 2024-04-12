dissect_notify_field(tvbuff_t *tvb, int offset, packet_info *pinfo,
		     proto_tree *tree, dcerpc_info *di, guint8 *drep, guint16 type,
		     guint16 *data)
{
	guint16 field;
	const char *str;

	offset = dissect_ndr_uint16(
		tvb, offset, pinfo, NULL, di, drep,
		hf_notify_field, &field);

	switch(type) {
	case PRINTER_NOTIFY_TYPE:
		str = val_to_str_ext_const(field, &printer_notify_option_data_vals_ext,
				 "Unknown");
		break;
	case JOB_NOTIFY_TYPE:
		str = val_to_str_ext_const(field, &job_notify_option_data_vals_ext,
				 "Unknown");
		break;
	default:
		str = "Unknown notify type";
		break;
	}

	proto_tree_add_uint_format_value(tree, hf_notify_field, tvb, offset - 2, 2, field, "%s (%d)", str, field);

	if (data)
		*data = field;

	return offset;
}
