static int orinoco_ioctl_set_mlme(struct net_device *dev,
				  struct iw_request_info *info,
				  union iwreq_data *wrqu, char *extra)
{
	struct orinoco_private *priv = ndev_priv(dev);
	struct iw_mlme *mlme = (struct iw_mlme *)extra;
	unsigned long flags;
	int ret = 0;

	if (orinoco_lock(priv, &flags) != 0)
		return -EBUSY;

	switch (mlme->cmd) {
	case IW_MLME_DEAUTH:
		/* silently ignore */
		break;

	case IW_MLME_DISASSOC:

		ret = orinoco_hw_disassociate(priv, mlme->addr.sa_data,
					      mlme->reason_code);
		break;

	default:
		ret = -EOPNOTSUPP;
	}

	orinoco_unlock(priv, &flags);
	return ret;
}
