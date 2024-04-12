dissect_PRINTER_INFO_7(tvbuff_t *tvb, int offset,
				  packet_info *pinfo, proto_tree *tree,
				  dcerpc_info *di, guint8 *drep)
{
	offset = dissect_spoolss_relstr(
		tvb, offset, pinfo, tree, di, drep, hf_printer_guid,
		0, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep,
		hf_printer_action, NULL);

	return offset;
}
