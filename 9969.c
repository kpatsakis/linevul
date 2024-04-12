static int platform_drv_remove(struct device *_dev)
{
	struct platform_driver *drv = to_platform_driver(_dev->driver);
	struct platform_device *dev = to_platform_device(_dev);
	int ret = 0;

	if (drv->remove)
		ret = drv->remove(dev);
	dev_pm_domain_detach(_dev, true);

	return ret;
}
