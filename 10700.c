static void hns_gmac_set_duplex_type(void *mac_drv, u8 newval)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	dsaf_set_dev_bit(drv, GMAC_DUPLEX_TYPE_REG,
			 GMAC_DUPLEX_TYPE_B, !!newval);
}
