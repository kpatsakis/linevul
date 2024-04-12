static void hns_rcb_ring_get_cfg(struct hnae_queue *q, int ring_type)
{
	struct hnae_ring *ring;
	struct rcb_common_cb *rcb_common;
	struct ring_pair_cb *ring_pair_cb;
	u16 desc_num, mdnum_ppkt;
	bool irq_idx, is_ver1;

	ring_pair_cb = container_of(q, struct ring_pair_cb, q);
	is_ver1 = AE_IS_VER1(ring_pair_cb->rcb_common->dsaf_dev->dsaf_ver);
	if (ring_type == RX_RING) {
		ring = &q->rx_ring;
		ring->io_base = ring_pair_cb->q.io_base;
		irq_idx = HNS_RCB_IRQ_IDX_RX;
		mdnum_ppkt = HNS_RCB_RING_MAX_BD_PER_PKT;
	} else {
		ring = &q->tx_ring;
		ring->io_base = (u8 __iomem *)ring_pair_cb->q.io_base +
			HNS_RCB_TX_REG_OFFSET;
		irq_idx = HNS_RCB_IRQ_IDX_TX;
		mdnum_ppkt = is_ver1 ? HNS_RCB_RING_MAX_TXBD_PER_PKT :
				 HNS_RCBV2_RING_MAX_TXBD_PER_PKT;
	}

	rcb_common = ring_pair_cb->rcb_common;
	desc_num = rcb_common->dsaf_dev->desc_num;

	ring->desc = NULL;
	ring->desc_cb = NULL;

	ring->irq = ring_pair_cb->virq[irq_idx];
	ring->desc_dma_addr = 0;

	ring->buf_size = RCB_DEFAULT_BUFFER_SIZE;
	ring->desc_num = desc_num;
	ring->max_desc_num_per_pkt = mdnum_ppkt;
	ring->max_raw_data_sz_per_desc = HNS_RCB_MAX_PKT_SIZE;
	ring->max_pkt_size = HNS_RCB_MAX_PKT_SIZE;
	ring->next_to_use = 0;
	ring->next_to_clean = 0;
}
