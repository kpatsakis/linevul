static int efx_fill_loopback_test(struct efx_nic *efx,
				  struct efx_loopback_self_tests *lb_tests,
				  enum efx_loopback_mode mode,
				  unsigned int test_index,
				  struct ethtool_string *strings, u64 *data)
{
	struct efx_channel *channel = efx_get_channel(efx, 0);
	struct efx_tx_queue *tx_queue;

	efx_for_each_channel_tx_queue(tx_queue, channel) {
		efx_fill_test(test_index++, strings, data,
			      &lb_tests->tx_sent[tx_queue->queue],
			      EFX_TX_QUEUE_NAME(tx_queue),
			      EFX_LOOPBACK_NAME(mode, "tx_sent"));
		efx_fill_test(test_index++, strings, data,
			      &lb_tests->tx_done[tx_queue->queue],
			      EFX_TX_QUEUE_NAME(tx_queue),
			      EFX_LOOPBACK_NAME(mode, "tx_done"));
	}
	efx_fill_test(test_index++, strings, data,
		      &lb_tests->rx_good,
		      "rx", 0,
		      EFX_LOOPBACK_NAME(mode, "rx_good"));
	efx_fill_test(test_index++, strings, data,
		      &lb_tests->rx_bad,
		      "rx", 0,
		      EFX_LOOPBACK_NAME(mode, "rx_bad"));

	return test_index;
}
