dissect_SPOOL_PRINTER_INFO(tvbuff_t *tvb, int offset, packet_info *pinfo,
			   proto_tree *tree, dcerpc_info *di, guint8 *drep)
{
	proto_tree *subtree;
	guint32 level;
	proto_tree *item;

	subtree = proto_tree_add_subtree(
		tree, tvb, offset, 0, ett_SPOOL_PRINTER_INFO_LEVEL, &item, "Spool printer info level");

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, subtree, di, drep, hf_level, &level);

	switch(level) {
	case 3: {
		guint32 devmode_ptr, secdesc_ptr;

		/* I can't seem to get this working with the correct
		   dissect_ndr_pointer() function so let's cheat and
		   dissect the pointers by hand. )-: */

		offset = dissect_ndr_uint32(
			tvb, offset, pinfo, subtree, di, drep,
			hf_spool_printer_info_devmode_ptr,
			&devmode_ptr);

		offset = dissect_ndr_uint32(
			tvb, offset, pinfo, subtree, di, drep,
			hf_spool_printer_info_secdesc_ptr,
			&secdesc_ptr);

		if (devmode_ptr)
			offset = dissect_DEVMODE_CTR(
				tvb, offset, pinfo, subtree, di, drep);

		if (secdesc_ptr)
			offset = dissect_SEC_DESC_BUF(
				tvb, offset, pinfo, subtree, di, drep);

	break;
	}
	case 2:
	default:
		expert_add_info_format(pinfo, item, &ei_spool_printer_info_level, "Unknown spool printer info level %d", level);
		break;
	}

	return offset;
}
