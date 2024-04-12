static int nl80211_send_station(struct sk_buff *msg, u32 pid, u32 seq,
				int flags, struct net_device *dev,
				const u8 *mac_addr, struct station_info *sinfo)
{
	void *hdr;
	struct nlattr *sinfoattr, *bss_param;

	hdr = nl80211hdr_put(msg, pid, seq, flags, NL80211_CMD_NEW_STATION);
	if (!hdr)
		return -1;

	NLA_PUT_U32(msg, NL80211_ATTR_IFINDEX, dev->ifindex);
	NLA_PUT(msg, NL80211_ATTR_MAC, ETH_ALEN, mac_addr);

	NLA_PUT_U32(msg, NL80211_ATTR_GENERATION, sinfo->generation);

	sinfoattr = nla_nest_start(msg, NL80211_ATTR_STA_INFO);
	if (!sinfoattr)
		goto nla_put_failure;
	if (sinfo->filled & STATION_INFO_CONNECTED_TIME)
		NLA_PUT_U32(msg, NL80211_STA_INFO_CONNECTED_TIME,
			    sinfo->connected_time);
	if (sinfo->filled & STATION_INFO_INACTIVE_TIME)
		NLA_PUT_U32(msg, NL80211_STA_INFO_INACTIVE_TIME,
			    sinfo->inactive_time);
	if (sinfo->filled & STATION_INFO_RX_BYTES)
		NLA_PUT_U32(msg, NL80211_STA_INFO_RX_BYTES,
			    sinfo->rx_bytes);
	if (sinfo->filled & STATION_INFO_TX_BYTES)
		NLA_PUT_U32(msg, NL80211_STA_INFO_TX_BYTES,
			    sinfo->tx_bytes);
	if (sinfo->filled & STATION_INFO_LLID)
		NLA_PUT_U16(msg, NL80211_STA_INFO_LLID,
			    sinfo->llid);
	if (sinfo->filled & STATION_INFO_PLID)
		NLA_PUT_U16(msg, NL80211_STA_INFO_PLID,
			    sinfo->plid);
	if (sinfo->filled & STATION_INFO_PLINK_STATE)
		NLA_PUT_U8(msg, NL80211_STA_INFO_PLINK_STATE,
			    sinfo->plink_state);
	if (sinfo->filled & STATION_INFO_SIGNAL)
		NLA_PUT_U8(msg, NL80211_STA_INFO_SIGNAL,
			   sinfo->signal);
	if (sinfo->filled & STATION_INFO_SIGNAL_AVG)
		NLA_PUT_U8(msg, NL80211_STA_INFO_SIGNAL_AVG,
			   sinfo->signal_avg);
	if (sinfo->filled & STATION_INFO_TX_BITRATE) {
		if (!nl80211_put_sta_rate(msg, &sinfo->txrate,
					  NL80211_STA_INFO_TX_BITRATE))
			goto nla_put_failure;
	}
	if (sinfo->filled & STATION_INFO_RX_BITRATE) {
		if (!nl80211_put_sta_rate(msg, &sinfo->rxrate,
					  NL80211_STA_INFO_RX_BITRATE))
			goto nla_put_failure;
	}
	if (sinfo->filled & STATION_INFO_RX_PACKETS)
		NLA_PUT_U32(msg, NL80211_STA_INFO_RX_PACKETS,
			    sinfo->rx_packets);
	if (sinfo->filled & STATION_INFO_TX_PACKETS)
		NLA_PUT_U32(msg, NL80211_STA_INFO_TX_PACKETS,
			    sinfo->tx_packets);
	if (sinfo->filled & STATION_INFO_TX_RETRIES)
		NLA_PUT_U32(msg, NL80211_STA_INFO_TX_RETRIES,
			    sinfo->tx_retries);
	if (sinfo->filled & STATION_INFO_TX_FAILED)
		NLA_PUT_U32(msg, NL80211_STA_INFO_TX_FAILED,
			    sinfo->tx_failed);
	if (sinfo->filled & STATION_INFO_BSS_PARAM) {
		bss_param = nla_nest_start(msg, NL80211_STA_INFO_BSS_PARAM);
		if (!bss_param)
			goto nla_put_failure;

		if (sinfo->bss_param.flags & BSS_PARAM_FLAGS_CTS_PROT)
			NLA_PUT_FLAG(msg, NL80211_STA_BSS_PARAM_CTS_PROT);
		if (sinfo->bss_param.flags & BSS_PARAM_FLAGS_SHORT_PREAMBLE)
			NLA_PUT_FLAG(msg, NL80211_STA_BSS_PARAM_SHORT_PREAMBLE);
		if (sinfo->bss_param.flags & BSS_PARAM_FLAGS_SHORT_SLOT_TIME)
			NLA_PUT_FLAG(msg,
				     NL80211_STA_BSS_PARAM_SHORT_SLOT_TIME);
		NLA_PUT_U8(msg, NL80211_STA_BSS_PARAM_DTIM_PERIOD,
			   sinfo->bss_param.dtim_period);
		NLA_PUT_U16(msg, NL80211_STA_BSS_PARAM_BEACON_INTERVAL,
			    sinfo->bss_param.beacon_interval);

		nla_nest_end(msg, bss_param);
	}
	nla_nest_end(msg, sinfoattr);

	return genlmsg_end(msg, hdr);

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}
