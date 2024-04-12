static int airo_open(struct net_device *dev) {
	struct airo_info *ai = dev->ml_priv;
	int rc = 0;

	if (test_bit(FLAG_FLASHING, &ai->flags))
		return -EIO;

	/* Make sure the card is configured.
	 * Wireless Extensions may postpone config changes until the card
	 * is open (to pipeline changes and speed-up card setup). If
	 * those changes are not yet committed, do it now - Jean II */
	if (test_bit(FLAG_COMMIT, &ai->flags)) {
		disable_MAC(ai, 1);
		writeConfigRid(ai, 1);
	}

	if (ai->wifidev != dev) {
		clear_bit(JOB_DIE, &ai->jobs);
		ai->airo_thread_task = kthread_run(airo_thread, dev, dev->name);
		if (IS_ERR(ai->airo_thread_task))
			return (int)PTR_ERR(ai->airo_thread_task);

		rc = request_irq(dev->irq, airo_interrupt, IRQF_SHARED,
			dev->name, dev);
		if (rc) {
			airo_print_err(dev->name,
				"register interrupt %d failed, rc %d",
				dev->irq, rc);
			set_bit(JOB_DIE, &ai->jobs);
			kthread_stop(ai->airo_thread_task);
			return rc;
		}

		/* Power on the MAC controller (which may have been disabled) */
		clear_bit(FLAG_RADIO_DOWN, &ai->flags);
		enable_interrupts(ai);

		try_auto_wep(ai);
	}
	enable_MAC(ai, 1);

	netif_start_queue(dev);
	return 0;
}
