static noinline int mmc_ioctl_cdrom_read_audio(struct cdrom_device_info *cdi,
					       void __user *arg)
{
	struct cdrom_read_audio ra;
	int lba;

	if (copy_from_user(&ra, (struct cdrom_read_audio __user *)arg,
			   sizeof(ra)))
		return -EFAULT;

	if (ra.addr_format == CDROM_MSF)
		lba = msf_to_lba(ra.addr.msf.minute,
				 ra.addr.msf.second,
				 ra.addr.msf.frame);
	else if (ra.addr_format == CDROM_LBA)
		lba = ra.addr.lba;
	else
		return -EINVAL;

	/* FIXME: we need upper bound checking, too!! */
	if (lba < 0 || ra.nframes <= 0 || ra.nframes > CD_FRAMES)
		return -EINVAL;

	return cdrom_read_cdda(cdi, ra.buf, lba, ra.nframes);
}
