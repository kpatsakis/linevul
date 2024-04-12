static void tg3_periodic_fetch_stats(struct tg3 *tp)
{
	struct tg3_hw_stats *sp = tp->hw_stats;

	if (!tp->link_up)
		return;

	TG3_STAT_ADD32(&sp->tx_octets, MAC_TX_STATS_OCTETS);
	TG3_STAT_ADD32(&sp->tx_collisions, MAC_TX_STATS_COLLISIONS);
	TG3_STAT_ADD32(&sp->tx_xon_sent, MAC_TX_STATS_XON_SENT);
	TG3_STAT_ADD32(&sp->tx_xoff_sent, MAC_TX_STATS_XOFF_SENT);
	TG3_STAT_ADD32(&sp->tx_mac_errors, MAC_TX_STATS_MAC_ERRORS);
	TG3_STAT_ADD32(&sp->tx_single_collisions, MAC_TX_STATS_SINGLE_COLLISIONS);
	TG3_STAT_ADD32(&sp->tx_mult_collisions, MAC_TX_STATS_MULT_COLLISIONS);
	TG3_STAT_ADD32(&sp->tx_deferred, MAC_TX_STATS_DEFERRED);
	TG3_STAT_ADD32(&sp->tx_excessive_collisions, MAC_TX_STATS_EXCESSIVE_COL);
	TG3_STAT_ADD32(&sp->tx_late_collisions, MAC_TX_STATS_LATE_COL);
	TG3_STAT_ADD32(&sp->tx_ucast_packets, MAC_TX_STATS_UCAST);
	TG3_STAT_ADD32(&sp->tx_mcast_packets, MAC_TX_STATS_MCAST);
	TG3_STAT_ADD32(&sp->tx_bcast_packets, MAC_TX_STATS_BCAST);
	if (unlikely(tg3_flag(tp, 5719_RDMA_BUG) &&
		     (sp->tx_ucast_packets.low + sp->tx_mcast_packets.low +
		      sp->tx_bcast_packets.low) > TG3_NUM_RDMA_CHANNELS)) {
		u32 val;

		val = tr32(TG3_LSO_RD_DMA_CRPTEN_CTRL);
		val &= ~TG3_LSO_RD_DMA_TX_LENGTH_WA;
		tw32(TG3_LSO_RD_DMA_CRPTEN_CTRL, val);
		tg3_flag_clear(tp, 5719_RDMA_BUG);
	}

	TG3_STAT_ADD32(&sp->rx_octets, MAC_RX_STATS_OCTETS);
	TG3_STAT_ADD32(&sp->rx_fragments, MAC_RX_STATS_FRAGMENTS);
	TG3_STAT_ADD32(&sp->rx_ucast_packets, MAC_RX_STATS_UCAST);
	TG3_STAT_ADD32(&sp->rx_mcast_packets, MAC_RX_STATS_MCAST);
	TG3_STAT_ADD32(&sp->rx_bcast_packets, MAC_RX_STATS_BCAST);
	TG3_STAT_ADD32(&sp->rx_fcs_errors, MAC_RX_STATS_FCS_ERRORS);
	TG3_STAT_ADD32(&sp->rx_align_errors, MAC_RX_STATS_ALIGN_ERRORS);
	TG3_STAT_ADD32(&sp->rx_xon_pause_rcvd, MAC_RX_STATS_XON_PAUSE_RECVD);
	TG3_STAT_ADD32(&sp->rx_xoff_pause_rcvd, MAC_RX_STATS_XOFF_PAUSE_RECVD);
	TG3_STAT_ADD32(&sp->rx_mac_ctrl_rcvd, MAC_RX_STATS_MAC_CTRL_RECVD);
	TG3_STAT_ADD32(&sp->rx_xoff_entered, MAC_RX_STATS_XOFF_ENTERED);
	TG3_STAT_ADD32(&sp->rx_frame_too_long_errors, MAC_RX_STATS_FRAME_TOO_LONG);
	TG3_STAT_ADD32(&sp->rx_jabbers, MAC_RX_STATS_JABBERS);
	TG3_STAT_ADD32(&sp->rx_undersize_packets, MAC_RX_STATS_UNDERSIZE);

	TG3_STAT_ADD32(&sp->rxbds_empty, RCVLPC_NO_RCV_BD_CNT);
	if (tg3_asic_rev(tp) != ASIC_REV_5717 &&
	    tg3_chip_rev_id(tp) != CHIPREV_ID_5719_A0 &&
	    tg3_chip_rev_id(tp) != CHIPREV_ID_5720_A0) {
		TG3_STAT_ADD32(&sp->rx_discards, RCVLPC_IN_DISCARDS_CNT);
	} else {
		u32 val = tr32(HOSTCC_FLOW_ATTN);
		val = (val & HOSTCC_FLOW_ATTN_MBUF_LWM) ? 1 : 0;
		if (val) {
			tw32(HOSTCC_FLOW_ATTN, HOSTCC_FLOW_ATTN_MBUF_LWM);
			sp->rx_discards.low += val;
			if (sp->rx_discards.low < val)
				sp->rx_discards.high += 1;
		}
		sp->mbuf_lwm_thresh_hit = sp->rx_discards;
	}
	TG3_STAT_ADD32(&sp->rx_errors, RCVLPC_IN_ERRORS_CNT);
}
