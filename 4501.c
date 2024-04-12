cifs_match_super(struct super_block *sb, void *data)
{
	struct cifs_mnt_data *mnt_data = (struct cifs_mnt_data *)data;
	struct smb_vol *volume_info;
	struct cifs_sb_info *cifs_sb;
	struct TCP_Server_Info *tcp_srv;
	struct cifs_ses *ses;
	struct cifs_tcon *tcon;
	struct tcon_link *tlink;
	int rc = 0;

	spin_lock(&cifs_tcp_ses_lock);
	cifs_sb = CIFS_SB(sb);
	tlink = cifs_get_tlink(cifs_sb_master_tlink(cifs_sb));
	if (IS_ERR(tlink)) {
		spin_unlock(&cifs_tcp_ses_lock);
		return rc;
	}
	tcon = tlink_tcon(tlink);
	ses = tcon->ses;
	tcp_srv = ses->server;

	volume_info = mnt_data->vol;

	if (!match_server(tcp_srv, volume_info) ||
	    !match_session(ses, volume_info) ||
	    !match_tcon(tcon, volume_info->UNC)) {
		rc = 0;
		goto out;
	}

	rc = compare_mount_options(sb, mnt_data);
out:
	spin_unlock(&cifs_tcp_ses_lock);
	cifs_put_tlink(tlink);
	return rc;
}
