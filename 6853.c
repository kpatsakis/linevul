static void efx_remove_eventq(struct efx_channel *channel)
{
	netif_dbg(channel->efx, drv, channel->efx->net_dev,
		  "chan %d remove event queue\n", channel->channel);

	efx_nic_remove_eventq(channel);
}
