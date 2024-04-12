void qrio_set_leds(void)
{
	u8 ctrlh;
	void __iomem *qrio_base = (void *)CONFIG_SYS_QRIO_BASE;

	/* set UNIT LED to RED and BOOT LED to ON */
	ctrlh = in_8(qrio_base + CTRLH_OFF);
	ctrlh |= (CTRLH_WRL_BOOT | CTRLH_WRL_UNITRUN);
	out_8(qrio_base + CTRLH_OFF, ctrlh);
}
