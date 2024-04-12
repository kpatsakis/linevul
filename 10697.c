static void efx_init_channels(struct efx_nic *efx)
{
	struct efx_tx_queue *tx_queue;
	struct efx_rx_queue *rx_queue;
	struct efx_channel *channel;

	/* Calculate the rx buffer allocation parameters required to
	 * support the current MTU, including padding for header
	 * alignment and overruns.
	 */
	efx->rx_buffer_len = (max(EFX_PAGE_IP_ALIGN, NET_IP_ALIGN) +
			      EFX_MAX_FRAME_LEN(efx->net_dev->mtu) +
			      efx->type->rx_buffer_hash_size +
			      efx->type->rx_buffer_padding);
	efx->rx_buffer_order = get_order(efx->rx_buffer_len +
					 sizeof(struct efx_rx_page_state));

	/* Initialise the channels */
	efx_for_each_channel(channel, efx) {
		netif_dbg(channel->efx, drv, channel->efx->net_dev,
			  "init chan %d\n", channel->channel);

		efx_init_eventq(channel);

		efx_for_each_channel_tx_queue(tx_queue, channel)
			efx_init_tx_queue(tx_queue);

		/* The rx buffer allocation strategy is MTU dependent */
		efx_rx_strategy(channel);

		efx_for_each_channel_rx_queue(rx_queue, channel)
			efx_init_rx_queue(rx_queue);

		WARN_ON(channel->rx_pkt != NULL);
		efx_rx_strategy(channel);
	}
}
