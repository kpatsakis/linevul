static int boco_clear_bits(u8 reg, u8 flags)
{
	int ret;
	u8 regval;

	/* give access to the EEPROM from FPGA */
	ret = i2c_read(BOCO_ADDR, reg, 1, &regval, 1);
	if (ret) {
		printf("%s: error reading the BOCO @%#x !!\n",
			__func__, reg);
		return ret;
	}
	regval &= ~flags;
	ret = i2c_write(BOCO_ADDR, reg, 1, &regval, 1);
	if (ret) {
		printf("%s: error writing the BOCO @%#x !!\n",
			__func__, reg);
		return ret;
	}

	return 0;
}
