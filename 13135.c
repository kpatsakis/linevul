static int airo_get_aplist(struct net_device *dev,
			   struct iw_request_info *info,
			   struct iw_point *dwrq,
			   char *extra)
{
	struct airo_info *local = dev->ml_priv;
	struct sockaddr *address = (struct sockaddr *) extra;
	struct iw_quality *qual;
	BSSListRid BSSList;
	int i;
	int loseSync = capable(CAP_NET_ADMIN) ? 1: -1;

	qual = kmalloc(IW_MAX_AP * sizeof(*qual), GFP_KERNEL);
	if (!qual)
		return -ENOMEM;

	for (i = 0; i < IW_MAX_AP; i++) {
		u16 dBm;
		if (readBSSListRid(local, loseSync, &BSSList))
			break;
		loseSync = 0;
		memcpy(address[i].sa_data, BSSList.bssid, ETH_ALEN);
		address[i].sa_family = ARPHRD_ETHER;
		dBm = le16_to_cpu(BSSList.dBm);
		if (local->rssi) {
			qual[i].level = 0x100 - dBm;
			qual[i].qual = airo_dbm_to_pct(local->rssi, dBm);
			qual[i].updated = IW_QUAL_QUAL_UPDATED
					| IW_QUAL_LEVEL_UPDATED
					| IW_QUAL_DBM;
		} else {
			qual[i].level = (dBm + 321) / 2;
			qual[i].qual = 0;
			qual[i].updated = IW_QUAL_QUAL_INVALID
					| IW_QUAL_LEVEL_UPDATED
					| IW_QUAL_DBM;
		}
		qual[i].noise = local->wstats.qual.noise;
		if (BSSList.index == cpu_to_le16(0xffff))
			break;
	}
	if (!i) {
		StatusRid status_rid;		/* Card status info */
		readStatusRid(local, &status_rid, 1);
		for (i = 0;
		     i < min(IW_MAX_AP, 4) &&
			     (status_rid.bssid[i][0]
			      & status_rid.bssid[i][1]
			      & status_rid.bssid[i][2]
			      & status_rid.bssid[i][3]
			      & status_rid.bssid[i][4]
			      & status_rid.bssid[i][5])!=0xff &&
			     (status_rid.bssid[i][0]
			      | status_rid.bssid[i][1]
			      | status_rid.bssid[i][2]
			      | status_rid.bssid[i][3]
			      | status_rid.bssid[i][4]
			      | status_rid.bssid[i][5]);
		     i++) {
			memcpy(address[i].sa_data,
			       status_rid.bssid[i], ETH_ALEN);
			address[i].sa_family = ARPHRD_ETHER;
		}
	} else {
		dwrq->flags = 1; /* Should be define'd */
		memcpy(extra + sizeof(struct sockaddr)*i,
		       &qual,  sizeof(struct iw_quality)*i);
	}
	dwrq->length = i;

	kfree(qual);
	return 0;
}
