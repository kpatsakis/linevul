static void mpi_receive_802_11(struct airo_info *ai)
{
	RxFid rxd;
	struct sk_buff *skb = NULL;
	u16 len, hdrlen = 0;
	__le16 fc;
	struct rx_hdr hdr;
	u16 gap;
	u16 *buffer;
	char *ptr = ai->rxfids[0].virtual_host_addr + 4;

	memcpy_fromio(&rxd, ai->rxfids[0].card_ram_off, sizeof(rxd));
	memcpy ((char *)&hdr, ptr, sizeof(hdr));
	ptr += sizeof(hdr);
	/* Bad CRC. Ignore packet */
	if (le16_to_cpu(hdr.status) & 2)
		hdr.len = 0;
	if (ai->wifidev == NULL)
		hdr.len = 0;
	len = le16_to_cpu(hdr.len);
	if (len > AIRO_DEF_MTU) {
		airo_print_err(ai->dev->name, "Bad size %d", len);
		goto badrx;
	}
	if (len == 0)
		goto badrx;

	fc = get_unaligned((__le16 *)ptr);
	hdrlen = header_len(fc);

	skb = dev_alloc_skb( len + hdrlen + 2 );
	if ( !skb ) {
		ai->dev->stats.rx_dropped++;
		goto badrx;
	}
	buffer = (u16*)skb_put (skb, len + hdrlen);
	memcpy ((char *)buffer, ptr, hdrlen);
	ptr += hdrlen;
	if (hdrlen == 24)
		ptr += 6;
	gap = get_unaligned_le16(ptr);
	ptr += sizeof(__le16);
	if (gap) {
		if (gap <= 8)
			ptr += gap;
		else
			airo_print_err(ai->dev->name,
			    "gaplen too big. Problems will follow...");
	}
	memcpy ((char *)buffer + hdrlen, ptr, len);
	ptr += len;
#ifdef IW_WIRELESS_SPY	  /* defined in iw_handler.h */
	if (ai->spy_data.spy_number > 0) {
		char *sa;
		struct iw_quality wstats;
		/* Prepare spy data : addr + qual */
		sa = (char*)buffer + 10;
		wstats.qual = hdr.rssi[0];
		if (ai->rssi)
			wstats.level = 0x100 - ai->rssi[hdr.rssi[1]].rssidBm;
		else
			wstats.level = (hdr.rssi[1] + 321) / 2;
		wstats.noise = ai->wstats.qual.noise;
		wstats.updated = IW_QUAL_QUAL_UPDATED
			| IW_QUAL_LEVEL_UPDATED
			| IW_QUAL_DBM;
		/* Update spy records */
		wireless_spy_update(ai->dev, sa, &wstats);
	}
#endif /* IW_WIRELESS_SPY */
	skb_reset_mac_header(skb);
	skb->pkt_type = PACKET_OTHERHOST;
	skb->dev = ai->wifidev;
	skb->protocol = htons(ETH_P_802_2);
	skb->ip_summed = CHECKSUM_NONE;
	netif_rx( skb );

badrx:
	if (rxd.valid == 0) {
		rxd.valid = 1;
		rxd.rdy = 0;
		rxd.len = PKTSIZE;
		memcpy_toio(ai->rxfids[0].card_ram_off, &rxd, sizeof(rxd));
	}
}
