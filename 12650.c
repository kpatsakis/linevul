static int airo_get_power(struct net_device *dev,
			  struct iw_request_info *info,
			  struct iw_param *vwrq,
			  char *extra)
{
	struct airo_info *local = dev->ml_priv;
	__le16 mode;

	readConfigRid(local, 1);
	mode = local->config.powerSaveMode;
	if ((vwrq->disabled = (mode == POWERSAVE_CAM)))
		return 0;
	if ((vwrq->flags & IW_POWER_TYPE) == IW_POWER_TIMEOUT) {
		vwrq->value = le16_to_cpu(local->config.fastListenDelay) * 1024;
		vwrq->flags = IW_POWER_TIMEOUT;
	} else {
		vwrq->value = le16_to_cpu(local->config.fastListenInterval) * 1024;
		vwrq->flags = IW_POWER_PERIOD;
	}
	if ((local->config.rmode & RXMODE_MASK) == RXMODE_ADDR)
		vwrq->flags |= IW_POWER_UNICAST_R;
	else
		vwrq->flags |= IW_POWER_ALL_R;

	return 0;
}
