get_vrrp_instance(const char *ifname, int vrid, int family)
{
	element e;
	vrrp_t *vrrp;

	if (LIST_ISEMPTY(vrrp_data->vrrp))
		return NULL;

	for (e = LIST_HEAD(vrrp_data->vrrp); e; ELEMENT_NEXT(e)) {
		vrrp = ELEMENT_DATA(e);

		if (vrrp->vrid == vrid &&
		    vrrp->family == family &&
		    !valid_path_cmp(IF_BASE_IFP(vrrp->ifp)->ifname, ifname))
				return vrrp;
	}

	return NULL;
}
