static bool nl80211_put_sta_rate(struct sk_buff *msg, struct rate_info *info,
				 int attr)
{
	struct nlattr *rate;
	u16 bitrate;

	rate = nla_nest_start(msg, attr);
	if (!rate)
		goto nla_put_failure;

	/* cfg80211_calculate_bitrate will return 0 for mcs >= 32 */
	bitrate = cfg80211_calculate_bitrate(info);
	if (bitrate > 0)
		NLA_PUT_U16(msg, NL80211_RATE_INFO_BITRATE, bitrate);

	if (info->flags & RATE_INFO_FLAGS_MCS)
		NLA_PUT_U8(msg, NL80211_RATE_INFO_MCS, info->mcs);
	if (info->flags & RATE_INFO_FLAGS_40_MHZ_WIDTH)
		NLA_PUT_FLAG(msg, NL80211_RATE_INFO_40_MHZ_WIDTH);
	if (info->flags & RATE_INFO_FLAGS_SHORT_GI)
		NLA_PUT_FLAG(msg, NL80211_RATE_INFO_SHORT_GI);

	nla_nest_end(msg, rate);
	return true;

nla_put_failure:
	return false;
}
