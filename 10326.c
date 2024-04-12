static int ipmi_init_msghandler(void)
{
	int rv;

	if (initialized)
		return 0;

	rv = driver_register(&ipmidriver.driver);
	if (rv) {
		pr_err("Could not register IPMI driver\n");
		return rv;
	}

	pr_info("version " IPMI_DRIVER_VERSION "\n");

	timer_setup(&ipmi_timer, ipmi_timeout, 0);
	mod_timer(&ipmi_timer, jiffies + IPMI_TIMEOUT_JIFFIES);

	atomic_notifier_chain_register(&panic_notifier_list, &panic_block);

	initialized = 1;

	return 0;
}
