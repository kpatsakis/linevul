static int dw2102_probe(struct usb_interface *intf,
		const struct usb_device_id *id)
{
	p1100 = kmemdup(&s6x0_properties,
			sizeof(struct dvb_usb_device_properties), GFP_KERNEL);
	if (!p1100)
		return -ENOMEM;
	/* copy default structure */
	/* fill only different fields */
	p1100->firmware = P1100_FIRMWARE;
	p1100->devices[0] = d1100;
	p1100->rc.core.rc_query = prof_rc_query;
	p1100->rc.core.rc_codes = RC_MAP_TBS_NEC;
	p1100->adapter->fe[0].frontend_attach = stv0288_frontend_attach;

	s660 = kmemdup(&s6x0_properties,
		       sizeof(struct dvb_usb_device_properties), GFP_KERNEL);
	if (!s660) {
		kfree(p1100);
		return -ENOMEM;
	}
	s660->firmware = S660_FIRMWARE;
	s660->num_device_descs = 3;
	s660->devices[0] = d660;
	s660->devices[1] = d480_1;
	s660->devices[2] = d480_2;
	s660->adapter->fe[0].frontend_attach = ds3000_frontend_attach;

	p7500 = kmemdup(&s6x0_properties,
			sizeof(struct dvb_usb_device_properties), GFP_KERNEL);
	if (!p7500) {
		kfree(p1100);
		kfree(s660);
		return -ENOMEM;
	}
	p7500->firmware = P7500_FIRMWARE;
	p7500->devices[0] = d7500;
	p7500->rc.core.rc_query = prof_rc_query;
	p7500->rc.core.rc_codes = RC_MAP_TBS_NEC;
	p7500->adapter->fe[0].frontend_attach = prof_7500_frontend_attach;


	s421 = kmemdup(&su3000_properties,
		       sizeof(struct dvb_usb_device_properties), GFP_KERNEL);
	if (!s421) {
		kfree(p1100);
		kfree(s660);
		kfree(p7500);
		return -ENOMEM;
	}
	s421->num_device_descs = 2;
	s421->devices[0] = d421;
	s421->devices[1] = d632;
	s421->adapter->fe[0].frontend_attach = m88rs2000_frontend_attach;

	if (0 == dvb_usb_device_init(intf, &dw2102_properties,
			THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, &dw2104_properties,
			THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, &dw3101_properties,
			THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, &s6x0_properties,
			THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, p1100,
			THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, s660,
			THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, p7500,
			THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, s421,
			THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, &su3000_properties,
			 THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, &t220_properties,
			 THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, &tt_s2_4600_properties,
			 THIS_MODULE, NULL, adapter_nr))
		return 0;

	return -ENODEV;
}
