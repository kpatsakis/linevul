int hush_init_var(void)
{
	ivm_analyze_eeprom(ivm_content, CONFIG_SYS_IVM_EEPROM_MAX_LEN);
	return 0;
}
