static int i8042_pm_thaw(struct device *dev)
{
	i8042_interrupt(0, NULL);

	return 0;
}
