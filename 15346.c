static int usb_dev_freeze(struct device *dev)
{
	return usb_suspend(dev, PMSG_FREEZE);
}
