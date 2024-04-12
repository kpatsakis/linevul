static void efx_ethtool_get_stats(struct net_device *net_dev,
				  struct ethtool_stats *stats,
				  u64 *data)
{
	struct efx_nic *efx = netdev_priv(net_dev);
	struct efx_mac_stats *mac_stats = &efx->mac_stats;
	struct efx_ethtool_stat *stat;
	struct efx_channel *channel;
	struct efx_tx_queue *tx_queue;
	struct rtnl_link_stats64 temp;
	int i;

	EFX_BUG_ON_PARANOID(stats->n_stats != EFX_ETHTOOL_NUM_STATS);

	/* Update MAC and NIC statistics */
	dev_get_stats(net_dev, &temp);

	/* Fill detailed statistics buffer */
	for (i = 0; i < EFX_ETHTOOL_NUM_STATS; i++) {
		stat = &efx_ethtool_stats[i];
		switch (stat->source) {
		case EFX_ETHTOOL_STAT_SOURCE_mac_stats:
			data[i] = stat->get_stat((void *)mac_stats +
						 stat->offset);
			break;
		case EFX_ETHTOOL_STAT_SOURCE_nic:
			data[i] = stat->get_stat((void *)efx + stat->offset);
			break;
		case EFX_ETHTOOL_STAT_SOURCE_channel:
			data[i] = 0;
			efx_for_each_channel(channel, efx)
				data[i] += stat->get_stat((void *)channel +
							  stat->offset);
			break;
		case EFX_ETHTOOL_STAT_SOURCE_tx_queue:
			data[i] = 0;
			efx_for_each_channel(channel, efx) {
				efx_for_each_channel_tx_queue(tx_queue, channel)
					data[i] +=
						stat->get_stat((void *)tx_queue
							       + stat->offset);
			}
			break;
		}
	}
}
