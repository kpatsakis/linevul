SpoolssAddPrinterEx_r(tvbuff_t *tvb, int offset, packet_info *pinfo,
				 proto_tree *tree, dcerpc_info *di, guint8 *drep _U_)
{
	dcerpc_call_value *dcv = (dcerpc_call_value *)di->call_data;
	e_ctx_hnd policy_hnd;
	proto_item *hnd_item;
	guint32 status;

	/* Parse packet */

	offset = dissect_nt_policy_hnd(
		tvb, offset, pinfo, tree, di, drep, hf_hnd, &policy_hnd, &hnd_item,
		TRUE, FALSE);

	offset = dissect_doserror(
		tvb, offset, pinfo, tree, di, drep, hf_rc, &status);

	if( status == 0 ){
		const char *pol_name;

		if (dcv->se_data){
			pol_name = wmem_strdup_printf(wmem_packet_scope(),
				"AddPrinterEx(%s)", (char *)dcv->se_data);
		} else {
			pol_name = "Unknown AddPrinterEx() handle";
		}
		if(!pinfo->fd->flags.visited){
			dcerpc_store_polhnd_name(&policy_hnd, pinfo, pol_name);
		}

		if(hnd_item)
			proto_item_append_text(hnd_item, ": %s", pol_name);
	}

	return offset;
}
