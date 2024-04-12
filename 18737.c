SpoolssStartPagePrinter_r(tvbuff_t *tvb, int offset,
				     packet_info *pinfo, proto_tree *tree,
				     dcerpc_info *di, guint8 *drep)
{
	/* Parse packet */

	offset = dissect_doserror(
		tvb, offset, pinfo, tree, di, drep, hf_rc, NULL);

	return offset;
}
