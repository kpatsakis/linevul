static void hns_gmac_set_mac_addr(void *mac_drv, char *mac_addr)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	u32 high_val = mac_addr[1] | (mac_addr[0] << 8);

	u32 low_val = mac_addr[5] | (mac_addr[4] << 8)
		| (mac_addr[3] << 16) | (mac_addr[2] << 24);

	u32 val = dsaf_read_dev(drv, GMAC_STATION_ADDR_HIGH_2_REG);
	u32 sta_addr_en = dsaf_get_bit(val, GMAC_ADDR_EN_B);

	dsaf_write_dev(drv, GMAC_STATION_ADDR_LOW_2_REG, low_val);
	dsaf_write_dev(drv, GMAC_STATION_ADDR_HIGH_2_REG,
		       high_val | (sta_addr_en << GMAC_ADDR_EN_B));
}
