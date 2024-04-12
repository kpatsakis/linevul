static int __init i8042_init(void)
{
	struct platform_device *pdev;
	int err;

	dbg_init();

	err = i8042_platform_init();
	if (err)
		return err;

	err = i8042_controller_check();
	if (err)
		goto err_platform_exit;

	pdev = platform_create_bundle(&i8042_driver, i8042_probe, NULL, 0, NULL, 0);
	if (IS_ERR(pdev)) {
		err = PTR_ERR(pdev);
		goto err_platform_exit;
	}

	bus_register_notifier(&serio_bus, &i8042_kbd_bind_notifier_block);
	panic_blink = i8042_panic_blink;

	return 0;

 err_platform_exit:
	i8042_platform_exit();
	return err;
}
