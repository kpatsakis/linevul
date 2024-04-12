static void sas_ata_flush_pm_eh(struct asd_sas_port *port, const char *func)
{
	struct domain_device *dev, *n;

	list_for_each_entry_safe(dev, n, &port->dev_list, dev_list_node) {
		if (!dev_is_sata(dev))
			continue;

		sas_ata_wait_eh(dev);

		/* if libata failed to power manage the device, tear it down */
		if (ata_dev_disabled(sas_to_ata_dev(dev)))
			sas_fail_probe(dev, func, -ENODEV);
	}
}
