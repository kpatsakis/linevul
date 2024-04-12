int sas_change_queue_depth(struct scsi_device *sdev, int depth)
{
	struct domain_device *dev = sdev_to_domain_dev(sdev);

	if (dev_is_sata(dev))
		return __ata_change_queue_depth(dev->sata_dev.ap, sdev, depth);

	if (!sdev->tagged_supported)
		depth = 1;
	return scsi_change_queue_depth(sdev, depth);
}
