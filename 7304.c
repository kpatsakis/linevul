static ssize_t sched_mc_power_savings_show(struct sysdev_class *class,
					   struct sysdev_class_attribute *attr,
					   char *page)
{
	return sprintf(page, "%u\n", sched_mc_power_savings);
}
