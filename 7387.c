SpoolssSetPrinter_q(tvbuff_t *tvb, int offset, packet_info *pinfo,
			       proto_tree *tree, dcerpc_info *di, guint8 *drep _U_)
{
	guint32 level;

	/* Parse packet */

	offset = dissect_nt_policy_hnd(
		tvb, offset, pinfo, tree, di, drep, hf_hnd, NULL, NULL,
		FALSE, FALSE);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_level, &level);

	col_append_fstr(pinfo->cinfo, COL_INFO, ", level %d", level);

	offset = dissect_SPOOL_PRINTER_INFO(
		tvb, offset, pinfo, tree, di, drep);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep,
		hf_setprinter_cmd, NULL);

	return offset;
}
