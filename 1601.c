static int nl80211_pre_doit(struct genl_ops *ops, struct sk_buff *skb,
			    struct genl_info *info)
{
	struct cfg80211_registered_device *rdev;
	struct net_device *dev;
	int err;
	bool rtnl = ops->internal_flags & NL80211_FLAG_NEED_RTNL;

	if (rtnl)
		rtnl_lock();

	if (ops->internal_flags & NL80211_FLAG_NEED_WIPHY) {
		rdev = cfg80211_get_dev_from_info(info);
		if (IS_ERR(rdev)) {
			if (rtnl)
				rtnl_unlock();
			return PTR_ERR(rdev);
		}
		info->user_ptr[0] = rdev;
	} else if (ops->internal_flags & NL80211_FLAG_NEED_NETDEV) {
		err = get_rdev_dev_by_info_ifindex(info, &rdev, &dev);
		if (err) {
			if (rtnl)
				rtnl_unlock();
			return err;
		}
		if (ops->internal_flags & NL80211_FLAG_CHECK_NETDEV_UP &&
		    !netif_running(dev)) {
			cfg80211_unlock_rdev(rdev);
			dev_put(dev);
			if (rtnl)
				rtnl_unlock();
			return -ENETDOWN;
		}
		info->user_ptr[0] = rdev;
		info->user_ptr[1] = dev;
	}

	return 0;
}
