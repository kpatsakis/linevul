static ssize_t pages_to_scan_store(struct kobject *kobj,
				   struct kobj_attribute *attr,
				   const char *buf, size_t count)
{
	int err;
	unsigned long pages;

	err = strict_strtoul(buf, 10, &pages);
	if (err || !pages || pages > UINT_MAX)
		return -EINVAL;

	khugepaged_pages_to_scan = pages;

	return count;
}
