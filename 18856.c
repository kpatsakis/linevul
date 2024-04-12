static ssize_t portio_type_show(struct kobject *kobj, struct attribute *attr,
			     char *buf)
{
	struct uio_portio *portio = to_portio(kobj);
	struct uio_port *port = portio->port;
	struct portio_sysfs_entry *entry;

	entry = container_of(attr, struct portio_sysfs_entry, attr);

	if (!entry->show)
		return -EIO;

	return entry->show(port, buf);
}
