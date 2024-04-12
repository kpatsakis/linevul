dissect_DEVMODE_fields(tvbuff_t *tvb, gint offset, packet_info *pinfo,
		       proto_tree *tree, dcerpc_info *di, guint8 *drep _U_, guint32 *pdata)
{
	guint32 fields;
	proto_item *hidden_item;

	static const int * hf_fields[] = {
		&hf_devmode_fields_orientation,
		&hf_devmode_fields_papersize,
		&hf_devmode_fields_paperlength,
		&hf_devmode_fields_paperwidth,
		&hf_devmode_fields_scale,
		&hf_devmode_fields_position,
		&hf_devmode_fields_nup,
		&hf_devmode_fields_copies,
		&hf_devmode_fields_defaultsource,
		&hf_devmode_fields_printquality,
		&hf_devmode_fields_color,
		&hf_devmode_fields_duplex,
		&hf_devmode_fields_yresolution,
		&hf_devmode_fields_ttoption,
		&hf_devmode_fields_collate,
		&hf_devmode_fields_formname,
		&hf_devmode_fields_logpixels,
		&hf_devmode_fields_bitsperpel,
		&hf_devmode_fields_pelswidth,
		&hf_devmode_fields_pelsheight,
		&hf_devmode_fields_displayflags,
		&hf_devmode_fields_displayfrequency,
		&hf_devmode_fields_icmmethod,
		&hf_devmode_fields_icmintent,
		&hf_devmode_fields_mediatype,
		&hf_devmode_fields_dithertype,
		&hf_devmode_fields_panningwidth,
		&hf_devmode_fields_panningheight,
		NULL
	};

	hidden_item = proto_tree_add_uint(
		tree, hf_devmode, tvb, offset, 0, 1);
	PROTO_ITEM_SET_HIDDEN(hidden_item);

	offset = dissect_ndr_uint32(tvb, offset, pinfo, NULL, di, drep, -1, &fields);

	proto_tree_add_bitmask_value_with_flags(tree, tvb, offset - 4, hf_devmode_fields,
					ett_DEVMODE_fields, hf_fields, fields, BMT_NO_APPEND);

	if (pdata)
		*pdata = fields;

	return offset;
}
