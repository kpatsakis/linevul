static struct ath_frame_info *get_frame_info(struct sk_buff *skb)
{
	struct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	BUILD_BUG_ON(sizeof(struct ath_frame_info) >
		     sizeof(tx_info->rate_driver_data));
	return (struct ath_frame_info *) &tx_info->rate_driver_data[0];
}
