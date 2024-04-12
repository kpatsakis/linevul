static int encryption_required(const struct cifs_tcon *tcon)
{
	if ((tcon->ses->session_flags & SMB2_SESSION_FLAG_ENCRYPT_DATA) ||
	    (tcon->share_flags & SHI1005_FLAGS_ENCRYPT_DATA))
		return 1;
	return 0;
}
