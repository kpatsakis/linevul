static void tg3_hwmon_close(struct tg3 *tp)
{
	if (tp->hwmon_dev) {
		hwmon_device_unregister(tp->hwmon_dev);
		tp->hwmon_dev = NULL;
		sysfs_remove_group(&tp->pdev->dev.kobj, &tg3_group);
	}
}
