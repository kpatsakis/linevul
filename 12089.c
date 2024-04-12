static void ieee80211_teardown_sdata(struct net_device *dev)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	struct ieee80211_local *local = sdata->local;
	int flushed;
	int i;

	/* free extra data */
	ieee80211_free_keys(sdata);

	ieee80211_debugfs_remove_netdev(sdata);

	for (i = 0; i < IEEE80211_FRAGMENT_MAX; i++)
		__skb_queue_purge(&sdata->fragments[i].skb_list);
	sdata->fragment_next = 0;

	if (ieee80211_vif_is_mesh(&sdata->vif))
		mesh_rmc_free(sdata);

	flushed = sta_info_flush(local, sdata);
	WARN_ON(flushed);
}
