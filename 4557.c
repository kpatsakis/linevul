static int uas_post_reset(struct usb_interface *intf)
{
	struct Scsi_Host *shost = usb_get_intfdata(intf);
	struct uas_dev_info *devinfo = (struct uas_dev_info *)shost->hostdata;
	unsigned long flags;
	int err;

	if (devinfo->shutdown)
		return 0;

	err = uas_configure_endpoints(devinfo);
	if (err) {
		shost_printk(KERN_ERR, shost,
			     "%s: alloc streams error %d after reset",
			     __func__, err);
		return 1;
	}

	spin_lock_irqsave(shost->host_lock, flags);
	scsi_report_bus_reset(shost, 0);
	spin_unlock_irqrestore(shost->host_lock, flags);

	scsi_unblock_requests(shost);

	return 0;
}
