SpoolssEnumPrinters_q(tvbuff_t *tvb, int offset, packet_info *pinfo,
				 proto_tree *tree, dcerpc_info *di, guint8 *drep _U_)
{
	guint32 level, flags;
	dcerpc_call_value *dcv = (dcerpc_call_value *)di->call_data;
	static const int * hf_flags[] = {
		&hf_enumprinters_flags_network,
		&hf_enumprinters_flags_shared,
		&hf_enumprinters_flags_remote,
		&hf_enumprinters_flags_name,
		&hf_enumprinters_flags_connections,
		&hf_enumprinters_flags_local,
		&hf_enumprinters_flags_default,
		NULL
	};

	/* Parse packet */

	offset = dissect_ndr_uint32(tvb, offset, pinfo, NULL, di, drep, -1, &flags);

	proto_tree_add_bitmask_value(tree, tvb, offset - 4, hf_enumprinters_flags,
					ett_enumprinters_flags, hf_flags, flags);

	offset = dissect_ndr_str_pointer_item(
		tvb, offset, pinfo, tree, di, drep,
		NDR_POINTER_UNIQUE, "Server name", hf_servername, 0);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_level, &level);

	/* GetPrinter() stores the level in se_data */
	if(!pinfo->fd->flags.visited){
		dcv->se_data = GINT_TO_POINTER((int)level);
	}

	col_append_fstr(pinfo->cinfo, COL_INFO, ", level %d", level);

	offset = dissect_spoolss_buffer(
		tvb, offset, pinfo, tree, di, drep, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_offered, NULL);

	return offset;
}
