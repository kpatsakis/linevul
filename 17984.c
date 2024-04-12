static ssize_t show_ibdev(struct device *dev, struct device_attribute *attr,
			  char *buf)
{
	struct ib_ucm_device *ucm_dev;

	ucm_dev = container_of(dev, struct ib_ucm_device, dev);
	return sprintf(buf, "%s\n", ucm_dev->ib_dev->name);
}
