int xenvif_schedulable(struct xenvif *vif)
{
	return netif_running(vif->dev) && netif_carrier_ok(vif->dev);
}
