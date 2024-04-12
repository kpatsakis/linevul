void qeth_core_get_ethtool_stats(struct net_device *dev,
		struct ethtool_stats *stats, u64 *data)
{
	struct qeth_card *card = dev->ml_priv;
	data[0] = card->stats.rx_packets -
				card->perf_stats.initial_rx_packets;
	data[1] = card->perf_stats.bufs_rec;
	data[2] = card->stats.tx_packets -
				card->perf_stats.initial_tx_packets;
	data[3] = card->perf_stats.bufs_sent;
	data[4] = card->stats.tx_packets - card->perf_stats.initial_tx_packets
			- card->perf_stats.skbs_sent_pack;
	data[5] = card->perf_stats.bufs_sent - card->perf_stats.bufs_sent_pack;
	data[6] = card->perf_stats.skbs_sent_pack;
	data[7] = card->perf_stats.bufs_sent_pack;
	data[8] = card->perf_stats.sg_skbs_sent;
	data[9] = card->perf_stats.sg_frags_sent;
	data[10] = card->perf_stats.sg_skbs_rx;
	data[11] = card->perf_stats.sg_frags_rx;
	data[12] = card->perf_stats.sg_alloc_page_rx;
	data[13] = (card->perf_stats.large_send_bytes >> 10);
	data[14] = card->perf_stats.large_send_cnt;
	data[15] = card->perf_stats.sc_dp_p;
	data[16] = card->perf_stats.sc_p_dp;
	data[17] = QETH_LOW_WATERMARK_PACK;
	data[18] = QETH_HIGH_WATERMARK_PACK;
	data[19] = atomic_read(&card->qdio.out_qs[0]->used_buffers);
	data[20] = (card->qdio.no_out_queues > 1) ?
			atomic_read(&card->qdio.out_qs[1]->used_buffers) : 0;
	data[21] = (card->qdio.no_out_queues > 2) ?
			atomic_read(&card->qdio.out_qs[2]->used_buffers) : 0;
	data[22] = (card->qdio.no_out_queues > 3) ?
			atomic_read(&card->qdio.out_qs[3]->used_buffers) : 0;
	data[23] = card->perf_stats.inbound_time;
	data[24] = card->perf_stats.inbound_cnt;
	data[25] = card->perf_stats.inbound_do_qdio_time;
	data[26] = card->perf_stats.inbound_do_qdio_cnt;
	data[27] = card->perf_stats.outbound_handler_time;
	data[28] = card->perf_stats.outbound_handler_cnt;
	data[29] = card->perf_stats.outbound_time;
	data[30] = card->perf_stats.outbound_cnt;
	data[31] = card->perf_stats.outbound_do_qdio_time;
	data[32] = card->perf_stats.outbound_do_qdio_cnt;
	data[33] = card->perf_stats.tx_csum;
	data[34] = card->perf_stats.tx_lin;
	data[35] = card->perf_stats.cq_cnt;
	data[36] = card->perf_stats.cq_time;
}
