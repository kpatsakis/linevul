int hns_rcb_set_coalesce_usecs(
	struct rcb_common_cb *rcb_common, u32 port_idx, u32 timeout)
{
	u32 old_timeout = hns_rcb_get_coalesce_usecs(rcb_common, port_idx);

	if (timeout == old_timeout)
		return 0;

	if (AE_IS_VER1(rcb_common->dsaf_dev->dsaf_ver)) {
		if (!HNS_DSAF_IS_DEBUG(rcb_common->dsaf_dev)) {
			dev_err(rcb_common->dsaf_dev->dev,
				"error: not support coalesce_usecs setting!\n");
			return -EINVAL;
		}
	}
	if (timeout > HNS_RCB_MAX_COALESCED_USECS || timeout == 0) {
		dev_err(rcb_common->dsaf_dev->dev,
			"error: coalesce_usecs setting supports 1~1023us\n");
		return -EINVAL;
	}
	hns_rcb_set_port_timeout(rcb_common, port_idx, timeout);
	return 0;
}
