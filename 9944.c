config_auth(
	config_tree *ptree
	)
{
	attr_val *	my_val;
	int		first;
	int		last;
	int		i;
#ifdef AUTOKEY
	int		item;
#endif

	/* Crypto Command */
#ifdef AUTOKEY
	item = -1;	/* quiet warning */
	my_val = HEAD_PFIFO(ptree->auth.crypto_cmd_list);
	for (; my_val != NULL; my_val = my_val->link) {
		switch (my_val->attr) {

		default:
			NTP_INSIST(0);
			break;

		case T_Host:
			item = CRYPTO_CONF_PRIV;
			break;

		case T_Ident:
			item = CRYPTO_CONF_IDENT;
			break;

		case T_Pw:
			item = CRYPTO_CONF_PW;
			break;

		case T_Randfile:
			item = CRYPTO_CONF_RAND;
			break;

		case T_Digest:
			item = CRYPTO_CONF_NID;
			break;
		}
		crypto_config(item, my_val->value.s);
	}
#endif	/* AUTOKEY */

	/* Keysdir Command */
	if (ptree->auth.keysdir) {
		if (keysdir != default_keysdir)
			free(keysdir);
		keysdir = estrdup(ptree->auth.keysdir);
	}


	/* ntp_signd_socket Command */
	if (ptree->auth.ntp_signd_socket) {
		if (ntp_signd_socket != default_ntp_signd_socket)
			free(ntp_signd_socket);
		ntp_signd_socket = estrdup(ptree->auth.ntp_signd_socket);
	}

#ifdef AUTOKEY
	if (ptree->auth.cryptosw && !cryptosw) {
		crypto_setup();
		cryptosw = 1;
	}
#endif	/* AUTOKEY */

	/* Keys Command */
	if (ptree->auth.keys)
		getauthkeys(ptree->auth.keys);

	/* Control Key Command */
	if (ptree->auth.control_key)
		ctl_auth_keyid = (keyid_t)ptree->auth.control_key;

	/* Requested Key Command */
	if (ptree->auth.request_key) {
		DPRINTF(4, ("set info_auth_keyid to %08lx\n",
			    (u_long) ptree->auth.request_key));
		info_auth_keyid = (keyid_t)ptree->auth.request_key;
	}

	/* Trusted Key Command */
	my_val = HEAD_PFIFO(ptree->auth.trusted_key_list);
	for (; my_val != NULL; my_val = my_val->link) {
		if (T_Integer == my_val->type)
			authtrust(my_val->value.i, 1);
		else if (T_Intrange == my_val->type) {
			first = my_val->value.r.first;
			last = my_val->value.r.last;
			if (first > last || first < 1 || last > 65534)
				msyslog(LOG_NOTICE,
					"Ignoring invalid trustedkey range %d ... %d, min 1 max 65534.",
					first, last);
			else
				for (i = first; i <= last; i++)
					authtrust((keyid_t)i, 1);
		}
	}

#ifdef AUTOKEY
	/* crypto revoke command */
	if (ptree->auth.revoke)
		sys_revoke = 1 << ptree->auth.revoke;
#endif	/* AUTOKEY */
}
