static int nl80211_set_wds_peer(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	const u8 *bssid;

	if (!info->attrs[NL80211_ATTR_MAC])
		return -EINVAL;

	if (netif_running(dev))
		return -EBUSY;

	if (!rdev->ops->set_wds_peer)
		return -EOPNOTSUPP;

	if (wdev->iftype != NL80211_IFTYPE_WDS)
		return -EOPNOTSUPP;

	bssid = nla_data(info->attrs[NL80211_ATTR_MAC]);
	return rdev->ops->set_wds_peer(wdev->wiphy, dev, bssid);
}
