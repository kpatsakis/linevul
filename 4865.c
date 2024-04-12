SpoolssEnumPrinters_r(tvbuff_t *tvb, int offset, packet_info *pinfo,
				 proto_tree *tree, dcerpc_info *di, guint8 *drep _U_)
{
	guint32 num_drivers;
	dcerpc_call_value *dcv = (dcerpc_call_value *)di->call_data;
	gint16 level = GPOINTER_TO_INT(dcv->se_data);
	BUFFER buffer;
	proto_item *item;
	proto_tree *subtree = NULL;

	col_append_fstr(pinfo->cinfo, COL_INFO, ", level %d", level);

	/* Parse packet */

	offset = dissect_spoolss_buffer(
		tvb, offset, pinfo, tree, di, drep, &buffer);

	if (buffer.tvb) {
		subtree = proto_tree_add_subtree_format( buffer.tree, buffer.tvb, 0, -1, ett_PRINTER_INFO, &item, "Print info level %d", level);

		switch(level) {
		case 0:
			dissect_PRINTER_INFO_0(
				buffer.tvb, 0, pinfo, subtree, di, drep);
			break;
		case 1:
			dissect_PRINTER_INFO_1(
				buffer.tvb, 0, pinfo, subtree, di, drep);
			break;
		case 2:
			dissect_PRINTER_INFO_2(
				buffer.tvb, 0, pinfo, subtree, di, drep);
			break;
		case 3:
			dissect_PRINTER_INFO_3(
				buffer.tvb, 0, pinfo, subtree, di, drep);
			break;
		case 7:
			dissect_PRINTER_INFO_7(
				buffer.tvb, 0, pinfo, subtree, di, drep);
			break;
		default:
			expert_add_info(pinfo, item, &ei_printer_info_level);
			break;
		}
	}

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_needed, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_returned,
		&num_drivers);

	offset = dissect_doserror(
		tvb, offset, pinfo, tree, di, drep, hf_rc, NULL);

	return offset;
}
