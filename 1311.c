void netdev_upper_dev_unlink(struct net_device *dev,
			     struct net_device *upper_dev)
{
	struct netdev_notifier_changeupper_info changeupper_info;
	struct netdev_adjacent *i, *j;
	ASSERT_RTNL();

	changeupper_info.upper_dev = upper_dev;
	changeupper_info.master = netdev_master_upper_dev_get(dev) == upper_dev;
	changeupper_info.linking = false;

	call_netdevice_notifiers_info(NETDEV_PRECHANGEUPPER, dev,
				      &changeupper_info.info);

	__netdev_adjacent_dev_unlink_neighbour(dev, upper_dev);

	/* Here is the tricky part. We must remove all dev's lower
	 * devices from all upper_dev's upper devices and vice
	 * versa, to maintain the graph relationship.
	 */
	list_for_each_entry(i, &dev->all_adj_list.lower, list)
		list_for_each_entry(j, &upper_dev->all_adj_list.upper, list)
			__netdev_adjacent_dev_unlink(i->dev, j->dev);

	/* remove also the devices itself from lower/upper device
	 * list
	 */
	list_for_each_entry(i, &dev->all_adj_list.lower, list)
		__netdev_adjacent_dev_unlink(i->dev, upper_dev);

	list_for_each_entry(i, &upper_dev->all_adj_list.upper, list)
		__netdev_adjacent_dev_unlink(dev, i->dev);

	call_netdevice_notifiers_info(NETDEV_CHANGEUPPER, dev,
				      &changeupper_info.info);
}
