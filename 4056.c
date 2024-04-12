get_hostkey_public_by_type(int type, int nid, struct ssh *ssh)
{
	return get_hostkey_by_type(type, nid, 0, ssh);
}
