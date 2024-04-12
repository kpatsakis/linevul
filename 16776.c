sess_auth_kerberos(struct sess_data *sess_data)
{
	int rc = 0;
	struct smb_hdr *smb_buf;
	SESSION_SETUP_ANDX *pSMB;
	char *bcc_ptr;
	struct cifs_ses *ses = sess_data->ses;
	__u32 capabilities;
	__u16 bytes_remaining;
	struct key *spnego_key = NULL;
	struct cifs_spnego_msg *msg;
	u16 blob_len;

	/* extended security */
	/* wct = 12 */
	rc = sess_alloc_buffer(sess_data, 12);
	if (rc)
		goto out;

	pSMB = (SESSION_SETUP_ANDX *)sess_data->iov[0].iov_base;
	bcc_ptr = sess_data->iov[2].iov_base;
	capabilities = cifs_ssetup_hdr(ses, pSMB);

	spnego_key = cifs_get_spnego_key(ses);
	if (IS_ERR(spnego_key)) {
		rc = PTR_ERR(spnego_key);
		spnego_key = NULL;
		goto out;
	}

	msg = spnego_key->payload.data[0];
	/*
	 * check version field to make sure that cifs.upcall is
	 * sending us a response in an expected form
	 */
	if (msg->version != CIFS_SPNEGO_UPCALL_VERSION) {
		cifs_dbg(VFS,
		  "incorrect version of cifs.upcall (expected %d but got %d)",
			      CIFS_SPNEGO_UPCALL_VERSION, msg->version);
		rc = -EKEYREJECTED;
		goto out_put_spnego_key;
	}

	ses->auth_key.response = kmemdup(msg->data, msg->sesskey_len,
					 GFP_KERNEL);
	if (!ses->auth_key.response) {
		cifs_dbg(VFS, "Kerberos can't allocate (%u bytes) memory",
				msg->sesskey_len);
		rc = -ENOMEM;
		goto out_put_spnego_key;
	}
	ses->auth_key.len = msg->sesskey_len;

	pSMB->req.hdr.Flags2 |= SMBFLG2_EXT_SEC;
	capabilities |= CAP_EXTENDED_SECURITY;
	pSMB->req.Capabilities = cpu_to_le32(capabilities);
	sess_data->iov[1].iov_base = msg->data + msg->sesskey_len;
	sess_data->iov[1].iov_len = msg->secblob_len;
	pSMB->req.SecurityBlobLength = cpu_to_le16(sess_data->iov[1].iov_len);

	if (ses->capabilities & CAP_UNICODE) {
		/* unicode strings must be word aligned */
		if ((sess_data->iov[0].iov_len
			+ sess_data->iov[1].iov_len) % 2) {
			*bcc_ptr = 0;
			bcc_ptr++;
		}
		unicode_oslm_strings(&bcc_ptr, sess_data->nls_cp);
		unicode_domain_string(&bcc_ptr, ses, sess_data->nls_cp);
	} else {
		/* BB: is this right? */
		ascii_ssetup_strings(&bcc_ptr, ses, sess_data->nls_cp);
	}

	sess_data->iov[2].iov_len = (long) bcc_ptr -
			(long) sess_data->iov[2].iov_base;

	rc = sess_sendreceive(sess_data);
	if (rc)
		goto out_put_spnego_key;

	pSMB = (SESSION_SETUP_ANDX *)sess_data->iov[0].iov_base;
	smb_buf = (struct smb_hdr *)sess_data->iov[0].iov_base;

	if (smb_buf->WordCount != 4) {
		rc = -EIO;
		cifs_dbg(VFS, "bad word count %d\n", smb_buf->WordCount);
		goto out_put_spnego_key;
	}

	if (le16_to_cpu(pSMB->resp.Action) & GUEST_LOGIN)
		cifs_dbg(FYI, "Guest login\n"); /* BB mark SesInfo struct? */

	ses->Suid = smb_buf->Uid;   /* UID left in wire format (le) */
	cifs_dbg(FYI, "UID = %llu\n", ses->Suid);

	bytes_remaining = get_bcc(smb_buf);
	bcc_ptr = pByteArea(smb_buf);

	blob_len = le16_to_cpu(pSMB->resp.SecurityBlobLength);
	if (blob_len > bytes_remaining) {
		cifs_dbg(VFS, "bad security blob length %d\n",
				blob_len);
		rc = -EINVAL;
		goto out_put_spnego_key;
	}
	bcc_ptr += blob_len;
	bytes_remaining -= blob_len;

	/* BB check if Unicode and decode strings */
	if (bytes_remaining == 0) {
		/* no string area to decode, do nothing */
	} else if (smb_buf->Flags2 & SMBFLG2_UNICODE) {
		/* unicode string area must be word-aligned */
		if (((unsigned long) bcc_ptr - (unsigned long) smb_buf) % 2) {
			++bcc_ptr;
			--bytes_remaining;
		}
		decode_unicode_ssetup(&bcc_ptr, bytes_remaining, ses,
				      sess_data->nls_cp);
	} else {
		decode_ascii_ssetup(&bcc_ptr, bytes_remaining, ses,
				    sess_data->nls_cp);
	}

	rc = sess_establish_session(sess_data);
out_put_spnego_key:
	key_invalidate(spnego_key);
	key_put(spnego_key);
out:
	sess_data->result = rc;
	sess_data->func = NULL;
	sess_free_buffer(sess_data);
	kfree(ses->auth_key.response);
	ses->auth_key.response = NULL;
}
