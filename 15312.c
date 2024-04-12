static netdev_features_t xenvif_fix_features(struct net_device *dev,
	netdev_features_t features)
{
	struct xenvif *vif = netdev_priv(dev);

	if (!vif->can_sg)
		features &= ~NETIF_F_SG;
	if (!vif->gso && !vif->gso_prefix)
		features &= ~NETIF_F_TSO;
	if (!vif->csum)
		features &= ~NETIF_F_IP_CSUM;

	return features;
}
