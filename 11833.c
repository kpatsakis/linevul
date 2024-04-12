static int pcd_open(struct cdrom_device_info *cdi, int purpose)
{
	struct pcd_unit *cd = cdi->handle;
	if (!cd->present)
		return -ENODEV;
	return 0;
}
