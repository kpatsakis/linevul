static void macvtap_exit(void)
{
	rtnl_link_unregister(&macvtap_link_ops);
	unregister_netdevice_notifier(&macvtap_notifier_block);
	class_unregister(macvtap_class);
	cdev_del(&macvtap_cdev);
	unregister_chrdev_region(macvtap_major, MACVTAP_NUM_DEVS);
}
