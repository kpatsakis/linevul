static int airo_get_name(struct net_device *dev,
			 struct iw_request_info *info,
			 char *cwrq,
			 char *extra)
{
	strcpy(cwrq, "IEEE 802.11-DS");
	return 0;
}
