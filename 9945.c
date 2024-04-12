query_info(const unsigned int xid, struct cifs_tcon *tcon,
	   u64 persistent_fid, u64 volatile_fid, u8 info_class,
	   size_t output_len, size_t min_len, void *data)
{
	struct smb2_query_info_req *req;
	struct smb2_query_info_rsp *rsp = NULL;
	struct kvec iov[2];
	struct kvec rsp_iov;
	int rc = 0;
	int resp_buftype;
	struct TCP_Server_Info *server;
	struct cifs_ses *ses = tcon->ses;
	int flags = 0;

	cifs_dbg(FYI, "Query Info\n");

	if (ses && (ses->server))
		server = ses->server;
	else
		return -EIO;

	rc = small_smb2_init(SMB2_QUERY_INFO, tcon, (void **) &req);
	if (rc)
		return rc;

	if (encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	req->InfoType = SMB2_O_INFO_FILE;
	req->FileInfoClass = info_class;
	req->PersistentFileId = persistent_fid;
	req->VolatileFileId = volatile_fid;
	/* 4 for rfc1002 length field and 1 for Buffer */
	req->InputBufferOffset =
		cpu_to_le16(sizeof(struct smb2_query_info_req) - 1 - 4);
	req->OutputBufferLength = cpu_to_le32(output_len);

	iov[0].iov_base = (char *)req;
	/* 4 for rfc1002 length field */
	iov[0].iov_len = get_rfc1002_length(req) + 4;

	rc = SendReceive2(xid, ses, iov, 1, &resp_buftype, flags, &rsp_iov);
	cifs_small_buf_release(req);
	rsp = (struct smb2_query_info_rsp *)rsp_iov.iov_base;

	if (rc) {
		cifs_stats_fail_inc(tcon, SMB2_QUERY_INFO_HE);
		goto qinf_exit;
	}

	rc = validate_and_copy_buf(le16_to_cpu(rsp->OutputBufferOffset),
				   le32_to_cpu(rsp->OutputBufferLength),
				   &rsp->hdr, min_len, data);

qinf_exit:
	free_rsp_buf(resp_buftype, rsp);
	return rc;
}
