static int ieee80211_stop(struct net_device *dev)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	ieee80211_do_stop(sdata, true);

	return 0;
}
