static int hns_gmac_adjust_link(void *mac_drv, enum mac_speed speed,
				u32 full_duplex)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	dsaf_set_dev_bit(drv, GMAC_DUPLEX_TYPE_REG,
			 GMAC_DUPLEX_TYPE_B, !!full_duplex);

	switch (speed) {
	case MAC_SPEED_10:
		dsaf_set_dev_field(
			drv, GMAC_PORT_MODE_REG,
			GMAC_PORT_MODE_M, GMAC_PORT_MODE_S, 0x6);
		break;
	case MAC_SPEED_100:
		dsaf_set_dev_field(
			drv, GMAC_PORT_MODE_REG,
			GMAC_PORT_MODE_M, GMAC_PORT_MODE_S, 0x7);
		break;
	case MAC_SPEED_1000:
		dsaf_set_dev_field(
			drv, GMAC_PORT_MODE_REG,
			GMAC_PORT_MODE_M, GMAC_PORT_MODE_S, 0x8);
		break;
	default:
		dev_err(drv->dev,
			"hns_gmac_adjust_link fail, speed%d mac%d\n",
			speed, drv->mac_id);
		return -EINVAL;
	}

	return 0;
}
