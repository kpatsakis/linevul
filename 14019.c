int fpga_reset(void)
{
	int ret = 0;
	u8 resets;

	if (!check_boco2()) {
		/* we do not have BOCO2, this is not really used */
		return 0;
	}

	/* if we have skipped, we only want to reset the PCIe part */
	resets = skip ? PCIE_RST : PCIE_RST | TRAFFIC_RST;

	ret = boco_clear_bits(PRST1, resets);
	if (ret)
		return ret;

	/* small delay for the pulse */
	udelay(10);

	ret = boco_set_bits(PRST1, resets);
	if (ret)
		return ret;

	return 0;
}
