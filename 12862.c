void smb1cli_conn_set_encryption(struct smbXcli_conn *conn,
				 struct smb_trans_enc_state *es)
{
	/* Replace the old state, if any. */
	if (conn->smb1.trans_enc) {
		TALLOC_FREE(conn->smb1.trans_enc);
	}
	conn->smb1.trans_enc = es;
}
