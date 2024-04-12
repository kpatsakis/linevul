SpoolssGetPrinterData_r(tvbuff_t *tvb, int offset,
				   packet_info *pinfo, proto_tree *tree,
				   dcerpc_info *di, guint8 *drep _U_)
{
	dcerpc_call_value *dcv = (dcerpc_call_value *)di->call_data;
	guint32 type;
	proto_item *hidden_item;
	const char *data;

	hidden_item = proto_tree_add_uint(
		tree, hf_printerdata, tvb, offset, 0, 1);
	PROTO_ITEM_SET_HIDDEN(hidden_item);

	/* Parse packet */

	offset = dissect_ndr_uint32(tvb, offset, pinfo, tree, di, drep,
				    hf_printerdata_type, &type);

	data = (const char *)(dcv->se_data ? dcv->se_data : "????");

	col_append_fstr(pinfo->cinfo, COL_INFO, ", %s", data);

	offset = dissect_printerdata_data(
		tvb, offset, pinfo, tree, di, drep, type);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_needed, NULL);

	offset = dissect_doserror(
		tvb, offset, pinfo, tree, di, drep, hf_rc, NULL);

	return offset;
}
