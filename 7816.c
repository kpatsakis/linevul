 static int su3000_read_mac_address(struct dvb_usb_device *d, u8 mac[6])
{
	int i;
	u8 obuf[] = { 0x1f, 0xf0 };
	u8 ibuf[] = { 0 };
	struct i2c_msg msg[] = {
		{
			.addr = 0x51,
			.flags = 0,
			.buf = obuf,
			.len = 2,
		}, {
			.addr = 0x51,
			.flags = I2C_M_RD,
			.buf = ibuf,
			.len = 1,

		}
	};

	for (i = 0; i < 6; i++) {
		obuf[1] = 0xf0 + i;
		if (i2c_transfer(&d->i2c_adap, msg, 2) != 2)
			break;
		else
			mac[i] = ibuf[0];
	}

	return 0;
}
