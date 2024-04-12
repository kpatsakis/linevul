SpoolssGetJob_q(tvbuff_t *tvb, int offset, packet_info *pinfo,
			   proto_tree *tree, dcerpc_info *di, guint8 *drep)
{
	dcerpc_call_value *dcv = (dcerpc_call_value *)di->call_data;
	guint32 level, jobid;

	/* Parse packet */

	offset = dissect_nt_policy_hnd(
		tvb, offset, pinfo, tree, di, drep, hf_hnd, NULL, NULL,
		FALSE, FALSE);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_job_id, &jobid);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_level, &level);

	/* GetJob() stores the level in se_data */
	if(!pinfo->fd->flags.visited){
			dcv->se_data = GUINT_TO_POINTER((int)level);
	}

	col_append_fstr(pinfo->cinfo, COL_INFO, ", level %d, jobid %d",
				level, jobid);

	offset = dissect_spoolss_buffer(tvb, offset, pinfo, tree, di, drep, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_offered, NULL);

	return offset;
}
