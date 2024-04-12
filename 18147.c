small_smb2_init(__le16 smb2_command, struct cifs_tcon *tcon,
		void **request_buf)
{
	int rc = 0;

	rc = smb2_reconnect(smb2_command, tcon);
	if (rc)
		return rc;

	/* BB eventually switch this to SMB2 specific small buf size */
	*request_buf = cifs_small_buf_get();
	if (*request_buf == NULL) {
		/* BB should we add a retry in here if not a writepage? */
		return -ENOMEM;
	}

	smb2_hdr_assemble((struct smb2_hdr *) *request_buf, smb2_command, tcon);

	if (tcon != NULL) {
#ifdef CONFIG_CIFS_STATS2
		uint16_t com_code = le16_to_cpu(smb2_command);
		cifs_stats_inc(&tcon->stats.smb2_stats.smb2_com_sent[com_code]);
#endif
		cifs_stats_inc(&tcon->num_smbs_sent);
	}

	return rc;
}
