int CIFS_SessSetup(const unsigned int xid, struct cifs_ses *ses,
		    const struct nls_table *nls_cp)
{
	int rc = 0;
	struct sess_data *sess_data;

	if (ses == NULL) {
		WARN(1, "%s: ses == NULL!", __func__);
		return -EINVAL;
	}

	sess_data = kzalloc(sizeof(struct sess_data), GFP_KERNEL);
	if (!sess_data)
		return -ENOMEM;

	rc = select_sec(ses, sess_data);
	if (rc)
		goto out;

	sess_data->xid = xid;
	sess_data->ses = ses;
	sess_data->buf0_type = CIFS_NO_BUFFER;
	sess_data->nls_cp = (struct nls_table *) nls_cp;

	while (sess_data->func)
		sess_data->func(sess_data);

	/* Store result before we free sess_data */
	rc = sess_data->result;

out:
	kfree(sess_data);
	return rc;
}
