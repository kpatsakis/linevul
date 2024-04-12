static int prof_7500_frontend_attach(struct dvb_usb_adapter *d)
{
	u8 obuf[] = {7, 1};

	d->fe_adap[0].fe = dvb_attach(stv0900_attach, &prof_7500_stv0900_config,
					&d->dev->i2c_adap, 0);
	if (d->fe_adap[0].fe == NULL)
		return -EIO;

	d->fe_adap[0].fe->ops.set_voltage = dw210x_set_voltage;

	dw210x_op_rw(d->dev->udev, 0x8a, 0, 0, obuf, 2, DW210X_WRITE_MSG);

	info("Attached STV0900+STB6100A!");

 	return 0;
 }
