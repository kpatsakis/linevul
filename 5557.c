int hns_rcb_common_init_hw(struct rcb_common_cb *rcb_common)
{
	u32 reg_val;
	int i;
	int port_num = hns_rcb_common_get_port_num(rcb_common);

	hns_rcb_comm_exc_irq_en(rcb_common, 0);

	reg_val = dsaf_read_dev(rcb_common, RCB_COM_CFG_INIT_FLAG_REG);
	if (0x1 != (reg_val & 0x1)) {
		dev_err(rcb_common->dsaf_dev->dev,
			"RCB_COM_CFG_INIT_FLAG_REG reg = 0x%x\n", reg_val);
		return -EBUSY;
	}

	for (i = 0; i < port_num; i++) {
		hns_rcb_set_port_desc_cnt(rcb_common, i, rcb_common->desc_num);
		hns_rcb_set_rx_coalesced_frames(
			rcb_common, i, HNS_RCB_DEF_RX_COALESCED_FRAMES);
		if (!AE_IS_VER1(rcb_common->dsaf_dev->dsaf_ver) &&
		    !HNS_DSAF_IS_DEBUG(rcb_common->dsaf_dev))
			hns_rcb_set_tx_coalesced_frames(
				rcb_common, i, HNS_RCB_DEF_TX_COALESCED_FRAMES);
		hns_rcb_set_port_timeout(
			rcb_common, i, HNS_RCB_DEF_COALESCED_USECS);
	}

	dsaf_write_dev(rcb_common, RCB_COM_CFG_ENDIAN_REG,
		       HNS_RCB_COMMON_ENDIAN);

	if (AE_IS_VER1(rcb_common->dsaf_dev->dsaf_ver)) {
		dsaf_write_dev(rcb_common, RCB_COM_CFG_FNA_REG, 0x0);
		dsaf_write_dev(rcb_common, RCB_COM_CFG_FA_REG, 0x1);
	} else {
		dsaf_set_dev_bit(rcb_common, RCBV2_COM_CFG_USER_REG,
				 RCB_COM_CFG_FNA_B, false);
		dsaf_set_dev_bit(rcb_common, RCBV2_COM_CFG_USER_REG,
				 RCB_COM_CFG_FA_B, true);
		dsaf_set_dev_bit(rcb_common, RCBV2_COM_CFG_TSO_MODE_REG,
				 RCB_COM_TSO_MODE_B, HNS_TSO_MODE_8BD_32K);
	}

	return 0;
}
