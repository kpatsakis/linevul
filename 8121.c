static int devinet_sysctl_register(struct in_device *idev)
{
	int err;

	if (!sysctl_dev_name_is_allowed(idev->dev->name))
		return -EINVAL;

	err = neigh_sysctl_register(idev->dev, idev->arp_parms, NULL);
	if (err)
		return err;
	err = __devinet_sysctl_register(dev_net(idev->dev), idev->dev->name,
					&idev->cnf);
	if (err)
		neigh_sysctl_unregister(idev->arp_parms);
	return err;
}
