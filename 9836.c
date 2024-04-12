static void __init parse_id(char *id)
{
	unsigned int vendor_id = 0, device_id = 0, flags = 0, i = 0;
	char *token, *name = NULL;

	if ((token = strsep(&id, ":")) != NULL)
		name = token;
	/* name now points to a null terminated string*/
	if ((token = strsep(&id, ":")) != NULL)
		vendor_id = simple_strtoul(token, NULL, 16);
	if ((token = strsep(&id, ":")) != NULL)
		device_id = simple_strtoul(token, NULL, 16);
	flags = simple_strtoul(id, NULL, 16);
	pr_info("%s: new device %s, vendor ID 0x%04x, device ID 0x%04x, flags: 0x%x\n",
		driver_name, name, vendor_id, device_id, flags);

	if (vendor_id > 0x10000 || vendor_id == 0)
		return;
	if (device_id > 0x10000 || device_id == 0)
		return;

	for (i = 0; usb_dev_id[i].name; i++);
	usb_dev_id[i].name = name;
	usb_dev_id[i].vendor = vendor_id;
	usb_dev_id[i].device = device_id;
	usb_dev_id[i].private = flags;
	pegasus_ids[i].match_flags = USB_DEVICE_ID_MATCH_DEVICE;
	pegasus_ids[i].idVendor = vendor_id;
	pegasus_ids[i].idProduct = device_id;
}
