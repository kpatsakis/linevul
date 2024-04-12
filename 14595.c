hostbased_key_allowed(struct passwd *pw, const char *cuser, char *chost,
    struct sshkey *key)
{
	struct ssh *ssh = active_state; /* XXX */
	const char *resolvedname, *ipaddr, *lookup, *reason;
	HostStatus host_status;
	int len;
	char *fp;

	if (auth_key_is_revoked(key))
		return 0;

	resolvedname = auth_get_canonical_hostname(ssh, options.use_dns);
	ipaddr = ssh_remote_ipaddr(ssh);

	debug2("%s: chost %s resolvedname %s ipaddr %s", __func__,
	    chost, resolvedname, ipaddr);

	if (((len = strlen(chost)) > 0) && chost[len - 1] == '.') {
		debug2("stripping trailing dot from chost %s", chost);
		chost[len - 1] = '\0';
	}

	if (options.hostbased_uses_name_from_packet_only) {
		if (auth_rhosts2(pw, cuser, chost, chost) == 0) {
			debug2("%s: auth_rhosts2 refused "
			    "user \"%.100s\" host \"%.100s\" (from packet)",
			    __func__, cuser, chost);
			return 0;
		}
		lookup = chost;
	} else {
		if (strcasecmp(resolvedname, chost) != 0)
			logit("userauth_hostbased mismatch: "
			    "client sends %s, but we resolve %s to %s",
			    chost, ipaddr, resolvedname);
		if (auth_rhosts2(pw, cuser, resolvedname, ipaddr) == 0) {
			debug2("%s: auth_rhosts2 refused "
			    "user \"%.100s\" host \"%.100s\" addr \"%.100s\"",
			    __func__, cuser, resolvedname, ipaddr);
			return 0;
		}
		lookup = resolvedname;
	}
	debug2("%s: access allowed by auth_rhosts2", __func__);

	if (sshkey_is_cert(key) &&
	    sshkey_cert_check_authority(key, 1, 0, lookup, &reason)) {
		error("%s", reason);
		auth_debug_add("%s", reason);
		return 0;
	}

	host_status = check_key_in_hostfiles(pw, key, lookup,
	    _PATH_SSH_SYSTEM_HOSTFILE,
	    options.ignore_user_known_hosts ? NULL : _PATH_SSH_USER_HOSTFILE);

	/* backward compat if no key has been found. */
	if (host_status == HOST_NEW) {
		host_status = check_key_in_hostfiles(pw, key, lookup,
		    _PATH_SSH_SYSTEM_HOSTFILE2,
		    options.ignore_user_known_hosts ? NULL :
		    _PATH_SSH_USER_HOSTFILE2);
	}

	if (host_status == HOST_OK) {
		if (sshkey_is_cert(key)) {
			if ((fp = sshkey_fingerprint(key->cert->signature_key,
			    options.fingerprint_hash, SSH_FP_DEFAULT)) == NULL)
				fatal("%s: sshkey_fingerprint fail", __func__);
			verbose("Accepted certificate ID \"%s\" signed by "
			    "%s CA %s from %s@%s", key->cert->key_id,
			    sshkey_type(key->cert->signature_key), fp,
			    cuser, lookup);
		} else {
			if ((fp = sshkey_fingerprint(key,
			    options.fingerprint_hash, SSH_FP_DEFAULT)) == NULL)
				fatal("%s: sshkey_fingerprint fail", __func__);
			verbose("Accepted %s public key %s from %s@%s",
			    sshkey_type(key), fp, cuser, lookup);
		}
		free(fp);
	}

	return (host_status == HOST_OK);
}
