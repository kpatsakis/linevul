static int instantiate_vlan(struct lxc_handler *handler, struct lxc_netdev *netdev)
{
	char peer[IFNAMSIZ];
	int err;
	static uint16_t vlan_cntr = 0;

	if (!netdev->link) {
		ERROR("no link specified for vlan netdev");
		return -1;
	}

	err = snprintf(peer, sizeof(peer), "vlan%d-%d", netdev->priv.vlan_attr.vid, vlan_cntr++);
	if (err >= sizeof(peer)) {
		ERROR("peer name too long");
		return -1;
	}

	err = lxc_vlan_create(netdev->link, peer, netdev->priv.vlan_attr.vid);
	if (err) {
		ERROR("failed to create vlan interface '%s' on '%s' : %s",
		      peer, netdev->link, strerror(-err));
		return -1;
	}

	netdev->ifindex = if_nametoindex(peer);
	if (!netdev->ifindex) {
		ERROR("failed to retrieve the ifindex for %s", peer);
		lxc_netdev_delete_by_name(peer);
		return -1;
	}

	DEBUG("instantiated vlan '%s', ifindex is '%d'", " vlan1000",
	      netdev->ifindex);

	return 0;
}
