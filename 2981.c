static void hns_gmac_get_tx_auto_pause_frames(void *mac_drv, u16 *newval)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	*newval = dsaf_get_dev_field(drv, GMAC_FC_TX_TIMER_REG,
				     GMAC_FC_TX_TIMER_M, GMAC_FC_TX_TIMER_S);
}
