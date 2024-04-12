exit_cifs_idmap(void)
{
	key_revoke(root_cred->thread_keyring);
	unregister_key_type(&cifs_idmap_key_type);
	put_cred(root_cred);
	cifs_dbg(FYI, "Unregistered %s key type\n", cifs_idmap_key_type.name);
}
