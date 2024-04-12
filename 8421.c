 static ssize_t k90_store_macro_mode(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf, size_t count)
{
	int ret;
	struct usb_interface *usbif = to_usb_interface(dev->parent);
	struct usb_device *usbdev = interface_to_usbdev(usbif);
	__u16 value;

	if (strncmp(buf, "SW", 2) == 0)
		value = K90_MACRO_MODE_SW;
	else if (strncmp(buf, "HW", 2) == 0)
		value = K90_MACRO_MODE_HW;
	else
		return -EINVAL;

	ret = usb_control_msg(usbdev, usb_sndctrlpipe(usbdev, 0),
			      K90_REQUEST_MACRO_MODE,
			      USB_DIR_OUT | USB_TYPE_VENDOR |
			      USB_RECIP_DEVICE, value, 0, NULL, 0,
			      USB_CTRL_SET_TIMEOUT);
	if (ret != 0) {
		dev_warn(dev, "Failed to set macro mode.\n");
		return ret;
	}

	return count;
}
