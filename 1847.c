static int nl80211_get_reg(struct sk_buff *skb, struct genl_info *info)
{
	struct sk_buff *msg;
	void *hdr = NULL;
	struct nlattr *nl_reg_rules;
	unsigned int i;
	int err = -EINVAL;

	mutex_lock(&cfg80211_mutex);

	if (!cfg80211_regdomain)
		goto out;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg) {
		err = -ENOBUFS;
		goto out;
	}

	hdr = nl80211hdr_put(msg, info->snd_pid, info->snd_seq, 0,
			     NL80211_CMD_GET_REG);
	if (!hdr)
		goto put_failure;

	NLA_PUT_STRING(msg, NL80211_ATTR_REG_ALPHA2,
		cfg80211_regdomain->alpha2);

	nl_reg_rules = nla_nest_start(msg, NL80211_ATTR_REG_RULES);
	if (!nl_reg_rules)
		goto nla_put_failure;

	for (i = 0; i < cfg80211_regdomain->n_reg_rules; i++) {
		struct nlattr *nl_reg_rule;
		const struct ieee80211_reg_rule *reg_rule;
		const struct ieee80211_freq_range *freq_range;
		const struct ieee80211_power_rule *power_rule;

		reg_rule = &cfg80211_regdomain->reg_rules[i];
		freq_range = &reg_rule->freq_range;
		power_rule = &reg_rule->power_rule;

		nl_reg_rule = nla_nest_start(msg, i);
		if (!nl_reg_rule)
			goto nla_put_failure;

		NLA_PUT_U32(msg, NL80211_ATTR_REG_RULE_FLAGS,
			reg_rule->flags);
		NLA_PUT_U32(msg, NL80211_ATTR_FREQ_RANGE_START,
			freq_range->start_freq_khz);
		NLA_PUT_U32(msg, NL80211_ATTR_FREQ_RANGE_END,
			freq_range->end_freq_khz);
		NLA_PUT_U32(msg, NL80211_ATTR_FREQ_RANGE_MAX_BW,
			freq_range->max_bandwidth_khz);
		NLA_PUT_U32(msg, NL80211_ATTR_POWER_RULE_MAX_ANT_GAIN,
			power_rule->max_antenna_gain);
		NLA_PUT_U32(msg, NL80211_ATTR_POWER_RULE_MAX_EIRP,
			power_rule->max_eirp);

		nla_nest_end(msg, nl_reg_rule);
	}

	nla_nest_end(msg, nl_reg_rules);

	genlmsg_end(msg, hdr);
	err = genlmsg_reply(msg, info);
	goto out;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
put_failure:
	nlmsg_free(msg);
	err = -EMSGSIZE;
out:
	mutex_unlock(&cfg80211_mutex);
	return err;
}
