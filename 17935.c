int eeprom_write_enable(unsigned dev_addr, int state)
{
	kw_gpio_set_value(KM_KIRKWOOD_ENV_WP, !state);

	return !kw_gpio_get_value(KM_KIRKWOOD_ENV_WP);
}
