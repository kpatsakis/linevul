cifs_find_smb_ses(struct TCP_Server_Info *server, struct smb_vol *vol)
{
	struct cifs_ses *ses;

	spin_lock(&cifs_tcp_ses_lock);
	list_for_each_entry(ses, &server->smb_ses_list, smb_ses_list) {
		if (!match_session(ses, vol))
			continue;
		++ses->ses_count;
		spin_unlock(&cifs_tcp_ses_lock);
		return ses;
	}
	spin_unlock(&cifs_tcp_ses_lock);
	return NULL;
}
