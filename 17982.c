int blk_get_device_by_str(const char *ifname, const char *dev_hwpart_str,
			  struct blk_desc **dev_desc)
{
	char *ep;
	char *dup_str = NULL;
	const char *dev_str, *hwpart_str;
	int dev, hwpart;

	hwpart_str = strchr(dev_hwpart_str, '.');
	if (hwpart_str) {
		dup_str = strdup(dev_hwpart_str);
		dup_str[hwpart_str - dev_hwpart_str] = 0;
		dev_str = dup_str;
		hwpart_str++;
	} else {
		dev_str = dev_hwpart_str;
		hwpart = 0;
	}

	dev = simple_strtoul(dev_str, &ep, 16);
	if (*ep) {
		printf("** Bad device specification %s %s **\n",
		       ifname, dev_str);
		dev = -EINVAL;
		goto cleanup;
	}

	if (hwpart_str) {
		hwpart = simple_strtoul(hwpart_str, &ep, 16);
		if (*ep) {
			printf("** Bad HW partition specification %s %s **\n",
			    ifname, hwpart_str);
			dev = -EINVAL;
			goto cleanup;
		}
	}

	*dev_desc = get_dev_hwpart(ifname, dev, hwpart);
	if (!(*dev_desc) || ((*dev_desc)->type == DEV_TYPE_UNKNOWN)) {
		debug("** Bad device %s %s **\n", ifname, dev_hwpart_str);
		dev = -ENOENT;
		goto cleanup;
	}

#ifdef CONFIG_HAVE_BLOCK_DEVICE
	/*
	 * Updates the partition table for the specified hw partition.
	 * Always should be done, otherwise hw partition 0 will return stale
	 * data after displaying a non-zero hw partition.
	 */
	part_init(*dev_desc);
#endif

cleanup:
	free(dup_str);
	return dev;
}
