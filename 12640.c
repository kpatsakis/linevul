static void macvlan_ethtool_get_drvinfo(struct net_device *dev,
					struct ethtool_drvinfo *drvinfo)
{
	snprintf(drvinfo->driver, 32, "macvlan");
	snprintf(drvinfo->version, 32, "0.1");
}
