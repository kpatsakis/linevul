dissect_NOTIFY_INFO(tvbuff_t *tvb, int offset, packet_info *pinfo,
		    proto_tree *tree, dcerpc_info *di, guint8 *drep)
{
	guint32 count;

	offset = dissect_ndr_uint32(tvb, offset, pinfo, tree, di, drep,
				    hf_notify_info_version, NULL);

	offset = dissect_ndr_uint32(tvb, offset, pinfo, tree, di, drep,
				    hf_notify_info_flags, NULL);

	offset = dissect_ndr_uint32(tvb, offset, pinfo, tree, di, drep,
				    hf_notify_info_count, &count);

	if (!di->conformant_run)
		col_append_fstr(
			pinfo->cinfo, COL_INFO, ", %d %s", count,
			notify_plural(count));

	offset = dissect_ndr_ucarray(tvb, offset, pinfo, tree, di, drep,
				     dissect_NOTIFY_INFO_DATA);

	return offset;
}
