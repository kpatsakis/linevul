void hns_rcbv2_int_ctrl_hw(struct hnae_queue *q, u32 flag, u32 mask)
{
	u32 int_mask_en = !!mask;

	if (flag & RCB_INT_FLAG_TX)
		dsaf_write_dev(q, RCB_RING_INTMSK_TXWL_REG, int_mask_en);

	if (flag & RCB_INT_FLAG_RX)
		dsaf_write_dev(q, RCB_RING_INTMSK_RXWL_REG, int_mask_en);
}
