static netdev_features_t netdev_fix_features(struct net_device *dev,
	netdev_features_t features)
{
	/* Fix illegal checksum combinations */
	if ((features & NETIF_F_HW_CSUM) &&
	    (features & (NETIF_F_IP_CSUM|NETIF_F_IPV6_CSUM))) {
		netdev_warn(dev, "mixed HW and IP checksum settings.\n");
		features &= ~(NETIF_F_IP_CSUM|NETIF_F_IPV6_CSUM);
	}

	/* TSO requires that SG is present as well. */
	if ((features & NETIF_F_ALL_TSO) && !(features & NETIF_F_SG)) {
		netdev_dbg(dev, "Dropping TSO features since no SG feature.\n");
		features &= ~NETIF_F_ALL_TSO;
	}

	if ((features & NETIF_F_TSO) && !(features & NETIF_F_HW_CSUM) &&
					!(features & NETIF_F_IP_CSUM)) {
		netdev_dbg(dev, "Dropping TSO features since no CSUM feature.\n");
		features &= ~NETIF_F_TSO;
		features &= ~NETIF_F_TSO_ECN;
	}

	if ((features & NETIF_F_TSO6) && !(features & NETIF_F_HW_CSUM) &&
					 !(features & NETIF_F_IPV6_CSUM)) {
		netdev_dbg(dev, "Dropping TSO6 features since no CSUM feature.\n");
		features &= ~NETIF_F_TSO6;
	}

	/* TSO ECN requires that TSO is present as well. */
	if ((features & NETIF_F_ALL_TSO) == NETIF_F_TSO_ECN)
		features &= ~NETIF_F_TSO_ECN;

	/* Software GSO depends on SG. */
	if ((features & NETIF_F_GSO) && !(features & NETIF_F_SG)) {
		netdev_dbg(dev, "Dropping NETIF_F_GSO since no SG feature.\n");
		features &= ~NETIF_F_GSO;
	}

	/* UFO needs SG and checksumming */
	if (features & NETIF_F_UFO) {
		/* maybe split UFO into V4 and V6? */
		if (!(features & NETIF_F_HW_CSUM) &&
		    ((features & (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM)) !=
		     (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM))) {
			netdev_dbg(dev,
				"Dropping NETIF_F_UFO since no checksum offload features.\n");
			features &= ~NETIF_F_UFO;
		}

		if (!(features & NETIF_F_SG)) {
			netdev_dbg(dev,
				"Dropping NETIF_F_UFO since no NETIF_F_SG feature.\n");
			features &= ~NETIF_F_UFO;
		}
	}

#ifdef CONFIG_NET_RX_BUSY_POLL
	if (dev->netdev_ops->ndo_busy_poll)
		features |= NETIF_F_BUSY_POLL;
	else
#endif
		features &= ~NETIF_F_BUSY_POLL;

	return features;
}
