int board_early_init_f(void)
{
	ccsr_gur_t *gur = (void *)(CONFIG_SYS_MPC85xx_GUTS_ADDR);
	bool cpuwd_flag = false;

	/* configure mode for uP reset request */
	qrio_uprstreq(UPREQ_CORE_RST);

	/* board only uses the DDR_MCK0, so disable the DDR_MCK1/2/3 */
	setbits_be32(&gur->ddrclkdr, 0x001f000f);

	/* set reset reason according CPU register */
	if ((gur->rstrqsr1 & (RSTRQSR1_WDT_RR | RSTRQSR1_SW_RR)) ==
	    RSTRQSR1_WDT_RR)
		cpuwd_flag = true;

	qrio_cpuwd_flag(cpuwd_flag);
	/* clear CPU bits by writing 1 */
	setbits_be32(&gur->rstrqsr1, RSTRQSR1_WDT_RR | RSTRQSR1_SW_RR);

	/* set the BFTIC's prstcfg to reset at power-up and unit reset only */
	qrio_prstcfg(BFTIC4_RST, PRSTCFG_POWUP_UNIT_RST);
	/* and enable WD on it */
	qrio_wdmask(BFTIC4_RST, true);

	/* set the ZL30138's prstcfg to reset at power-up only */
	qrio_prstcfg(ZL30158_RST, PRSTCFG_POWUP_RST);
	/* and take it out of reset as soon as possible (needed for Hooper) */
	qrio_prst(ZL30158_RST, false, false);

	return 0;
}
