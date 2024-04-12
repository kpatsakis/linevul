static void hns_xgmac_init(void *mac_drv)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;
	struct dsaf_device *dsaf_dev
		= (struct dsaf_device *)dev_get_drvdata(drv->dev);
	u32 port = drv->mac_id;

	dsaf_dev->misc_op->xge_srst(dsaf_dev, port, 0);
	mdelay(100);
	dsaf_dev->misc_op->xge_srst(dsaf_dev, port, 1);

	mdelay(100);
	hns_xgmac_lf_rf_control_init(drv);
	hns_xgmac_exc_irq_en(drv, 0);

	hns_xgmac_pma_fec_enable(drv, 0x0, 0x0);

	hns_xgmac_disable(mac_drv, MAC_COMM_MODE_RX_AND_TX);
}
