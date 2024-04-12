static int hns_nic_init_ring_data(struct hns_nic_priv *priv)
{
	struct hnae_handle *h = priv->ae_handle;
	struct hns_nic_ring_data *rd;
	bool is_ver1 = AE_IS_VER1(priv->enet_ver);
	int i;

	if (h->q_num > NIC_MAX_Q_PER_VF) {
		netdev_err(priv->netdev, "too much queue (%d)\n", h->q_num);
		return -EINVAL;
	}

	priv->ring_data = kzalloc(h->q_num * sizeof(*priv->ring_data) * 2,
				  GFP_KERNEL);
	if (!priv->ring_data)
		return -ENOMEM;

	for (i = 0; i < h->q_num; i++) {
		rd = &priv->ring_data[i];
		rd->queue_index = i;
		rd->ring = &h->qs[i]->tx_ring;
		rd->poll_one = hns_nic_tx_poll_one;
		rd->fini_process = is_ver1 ? hns_nic_tx_fini_pro :
			hns_nic_tx_fini_pro_v2;

		netif_napi_add(priv->netdev, &rd->napi,
			       hns_nic_common_poll, NIC_TX_CLEAN_MAX_NUM);
		rd->ring->irq_init_flag = RCB_IRQ_NOT_INITED;
	}
	for (i = h->q_num; i < h->q_num * 2; i++) {
		rd = &priv->ring_data[i];
		rd->queue_index = i - h->q_num;
		rd->ring = &h->qs[i - h->q_num]->rx_ring;
		rd->poll_one = hns_nic_rx_poll_one;
		rd->ex_process = hns_nic_rx_up_pro;
		rd->fini_process = is_ver1 ? hns_nic_rx_fini_pro :
			hns_nic_rx_fini_pro_v2;

		netif_napi_add(priv->netdev, &rd->napi,
			       hns_nic_common_poll, NIC_RX_CLEAN_MAX_NUM);
		rd->ring->irq_init_flag = RCB_IRQ_NOT_INITED;
	}

	return 0;
}
