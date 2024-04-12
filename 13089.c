sess_auth_rawntlmssp_negotiate(struct sess_data *sess_data)
{
	int rc;
	struct smb_hdr *smb_buf;
	SESSION_SETUP_ANDX *pSMB;
	struct cifs_ses *ses = sess_data->ses;
	__u16 bytes_remaining;
	char *bcc_ptr;
	u16 blob_len;

	cifs_dbg(FYI, "rawntlmssp session setup negotiate phase\n");

	/*
	 * if memory allocation is successful, caller of this function
	 * frees it.
	 */
	ses->ntlmssp = kmalloc(sizeof(struct ntlmssp_auth), GFP_KERNEL);
	if (!ses->ntlmssp) {
		rc = -ENOMEM;
		goto out;
	}
	ses->ntlmssp->sesskey_per_smbsess = false;

	/* wct = 12 */
	rc = sess_alloc_buffer(sess_data, 12);
	if (rc)
		goto out;

	pSMB = (SESSION_SETUP_ANDX *)sess_data->iov[0].iov_base;

	/* Build security blob before we assemble the request */
	build_ntlmssp_negotiate_blob(pSMB->req.SecurityBlob, ses);
	sess_data->iov[1].iov_len = sizeof(NEGOTIATE_MESSAGE);
	sess_data->iov[1].iov_base = pSMB->req.SecurityBlob;
	pSMB->req.SecurityBlobLength = cpu_to_le16(sizeof(NEGOTIATE_MESSAGE));

	rc = _sess_auth_rawntlmssp_assemble_req(sess_data);
	if (rc)
		goto out;

	rc = sess_sendreceive(sess_data);

	pSMB = (SESSION_SETUP_ANDX *)sess_data->iov[0].iov_base;
	smb_buf = (struct smb_hdr *)sess_data->iov[0].iov_base;

	/* If true, rc here is expected and not an error */
	if (sess_data->buf0_type != CIFS_NO_BUFFER &&
	    smb_buf->Status.CifsError ==
			cpu_to_le32(NT_STATUS_MORE_PROCESSING_REQUIRED))
		rc = 0;

	if (rc)
		goto out;

	cifs_dbg(FYI, "rawntlmssp session setup challenge phase\n");

	if (smb_buf->WordCount != 4) {
		rc = -EIO;
		cifs_dbg(VFS, "bad word count %d\n", smb_buf->WordCount);
		goto out;
	}

	ses->Suid = smb_buf->Uid;   /* UID left in wire format (le) */
	cifs_dbg(FYI, "UID = %llu\n", ses->Suid);

	bytes_remaining = get_bcc(smb_buf);
	bcc_ptr = pByteArea(smb_buf);

	blob_len = le16_to_cpu(pSMB->resp.SecurityBlobLength);
	if (blob_len > bytes_remaining) {
		cifs_dbg(VFS, "bad security blob length %d\n",
				blob_len);
		rc = -EINVAL;
		goto out;
	}

	rc = decode_ntlmssp_challenge(bcc_ptr, blob_len, ses);
out:
	sess_free_buffer(sess_data);

	if (!rc) {
		sess_data->func = sess_auth_rawntlmssp_authenticate;
		return;
	}

	/* Else error. Cleanup */
	kfree(ses->auth_key.response);
	ses->auth_key.response = NULL;
	kfree(ses->ntlmssp);
	ses->ntlmssp = NULL;

	sess_data->func = NULL;
	sess_data->result = rc;
}
