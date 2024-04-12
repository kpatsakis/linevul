get_connection_info(int populate, int use_dns)
{
	struct ssh *ssh = active_state; /* XXX */
	static struct connection_info ci;

	if (!populate)
		return &ci;
	ci.host = auth_get_canonical_hostname(ssh, use_dns);
	ci.address = ssh_remote_ipaddr(ssh);
	ci.laddress = ssh_local_ipaddr(ssh);
	ci.lport = ssh_local_port(ssh);
	return &ci;
}
