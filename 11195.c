static int unsupported_set_interface_altsetting(int sub_api, struct libusb_device_handle *dev_handle, int iface, int altsetting) {
	PRINT_UNSUPPORTED_API(set_interface_altsetting);
}
