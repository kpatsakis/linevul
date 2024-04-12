new_dev_store(struct mddev *mddev, const char *buf, size_t len)
{
	/* buf must be %d:%d\n? giving major and minor numbers */
	/* The new device is added to the array.
	 * If the array has a persistent superblock, we read the
	 * superblock to initialise info and check validity.
	 * Otherwise, only checking done is that in bind_rdev_to_array,
	 * which mainly checks size.
	 */
	char *e;
	int major = simple_strtoul(buf, &e, 10);
	int minor;
	dev_t dev;
	struct md_rdev *rdev;
	int err;

	if (!*buf || *e != ':' || !e[1] || e[1] == '\n')
		return -EINVAL;
	minor = simple_strtoul(e+1, &e, 10);
	if (*e && *e != '\n')
		return -EINVAL;
	dev = MKDEV(major, minor);
	if (major != MAJOR(dev) ||
	    minor != MINOR(dev))
		return -EOVERFLOW;

	flush_workqueue(md_misc_wq);

	err = mddev_lock(mddev);
	if (err)
		return err;
	if (mddev->persistent) {
		rdev = md_import_device(dev, mddev->major_version,
					mddev->minor_version);
		if (!IS_ERR(rdev) && !list_empty(&mddev->disks)) {
			struct md_rdev *rdev0
				= list_entry(mddev->disks.next,
					     struct md_rdev, same_set);
			err = super_types[mddev->major_version]
				.load_super(rdev, rdev0, mddev->minor_version);
			if (err < 0)
				goto out;
		}
	} else if (mddev->external)
		rdev = md_import_device(dev, -2, -1);
	else
		rdev = md_import_device(dev, -1, -1);

	if (IS_ERR(rdev)) {
		mddev_unlock(mddev);
		return PTR_ERR(rdev);
	}
	err = bind_rdev_to_array(rdev, mddev);
 out:
	if (err)
		export_rdev(rdev);
	mddev_unlock(mddev);
	return err ? err : len;
}
