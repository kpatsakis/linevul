static void edge_release(struct usb_serial *serial)
{
	kfree(usb_get_serial_data(serial));
}
