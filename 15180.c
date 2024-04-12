static void efx_fini_channels(struct efx_nic *efx)
{
	struct efx_channel *channel;
	struct efx_tx_queue *tx_queue;
	struct efx_rx_queue *rx_queue;
	int rc;

	EFX_ASSERT_RESET_SERIALISED(efx);
	BUG_ON(efx->port_enabled);

	rc = efx_nic_flush_queues(efx);
	if (rc && EFX_WORKAROUND_7803(efx)) {
		/* Schedule a reset to recover from the flush failure. The
		 * descriptor caches reference memory we're about to free,
		 * but falcon_reconfigure_mac_wrapper() won't reconnect
		 * the MACs because of the pending reset. */
		netif_err(efx, drv, efx->net_dev,
			  "Resetting to recover from flush failure\n");
		efx_schedule_reset(efx, RESET_TYPE_ALL);
	} else if (rc) {
		netif_err(efx, drv, efx->net_dev, "failed to flush queues\n");
	} else {
		netif_dbg(efx, drv, efx->net_dev,
			  "successfully flushed all queues\n");
	}

	efx_for_each_channel(channel, efx) {
		netif_dbg(channel->efx, drv, channel->efx->net_dev,
			  "shut down chan %d\n", channel->channel);

		efx_for_each_channel_rx_queue(rx_queue, channel)
			efx_fini_rx_queue(rx_queue);
		efx_for_each_possible_channel_tx_queue(tx_queue, channel)
			efx_fini_tx_queue(tx_queue);
		efx_fini_eventq(channel);
	}
}
