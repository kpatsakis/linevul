static int get_rdev_dev_by_info_ifindex(struct genl_info *info,
				       struct cfg80211_registered_device **rdev,
				       struct net_device **dev)
{
	struct nlattr **attrs = info->attrs;
	int ifindex;

	if (!attrs[NL80211_ATTR_IFINDEX])
		return -EINVAL;

	ifindex = nla_get_u32(attrs[NL80211_ATTR_IFINDEX]);
	*dev = dev_get_by_index(genl_info_net(info), ifindex);
	if (!*dev)
		return -ENODEV;

	*rdev = cfg80211_get_dev_from_ifindex(genl_info_net(info), ifindex);
	if (IS_ERR(*rdev)) {
		dev_put(*dev);
		return PTR_ERR(*rdev);
	}

	return 0;
}
