megasas_clear_intr_xscale(struct megasas_instance *instance)
{
	u32 status;
	u32 mfiStatus = 0;
	struct megasas_register_set __iomem *regs;
	regs = instance->reg_set;

	/*
	 * Check if it is our interrupt
	 */
	status = readl(&regs->outbound_intr_status);

	if (status & MFI_OB_INTR_STATUS_MASK)
		mfiStatus = MFI_INTR_FLAG_REPLY_MESSAGE;
	if (status & MFI_XSCALE_OMR0_CHANGE_INTERRUPT)
		mfiStatus |= MFI_INTR_FLAG_FIRMWARE_STATE_CHANGE;

	/*
	 * Clear the interrupt by writing back the same value
	 */
	if (mfiStatus)
		writel(status, &regs->outbound_intr_status);

	/* Dummy readl to force pci flush */
	readl(&regs->outbound_intr_status);

	return mfiStatus;
}
