static int nl80211_cancel_remain_on_channel(struct sk_buff *skb,
					    struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	u64 cookie;

	if (!info->attrs[NL80211_ATTR_COOKIE])
		return -EINVAL;

	if (!rdev->ops->cancel_remain_on_channel)
		return -EOPNOTSUPP;

	cookie = nla_get_u64(info->attrs[NL80211_ATTR_COOKIE]);

	return rdev->ops->cancel_remain_on_channel(&rdev->wiphy, dev, cookie);
}
