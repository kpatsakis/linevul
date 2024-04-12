static int __init macvlan_init_module(void)
{
	int err;

	register_netdevice_notifier(&macvlan_notifier_block);

	err = macvlan_link_register(&macvlan_link_ops);
	if (err < 0)
		goto err1;
	return 0;
err1:
	unregister_netdevice_notifier(&macvlan_notifier_block);
	return err;
}
