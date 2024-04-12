static void picolcd_remove(struct hid_device *hdev)
{
	struct picolcd_data *data = hid_get_drvdata(hdev);
	unsigned long flags;

	dbg_hid(PICOLCD_NAME " hardware remove...\n");
	spin_lock_irqsave(&data->lock, flags);
	data->status |= PICOLCD_FAILED;
	spin_unlock_irqrestore(&data->lock, flags);

	picolcd_exit_devfs(data);
	device_remove_file(&hdev->dev, &dev_attr_operation_mode);
	device_remove_file(&hdev->dev, &dev_attr_operation_mode_delay);
	hid_hw_close(hdev);
	hid_hw_stop(hdev);

	/* Shortcut potential pending reply that will never arrive */
	spin_lock_irqsave(&data->lock, flags);
	if (data->pending)
		complete(&data->pending->ready);
	spin_unlock_irqrestore(&data->lock, flags);

	/* Cleanup LED */
	picolcd_exit_leds(data);
	/* Clean up the framebuffer */
	picolcd_exit_backlight(data);
	picolcd_exit_lcd(data);
	picolcd_exit_framebuffer(data);
	/* Cleanup input */
	picolcd_exit_cir(data);
	picolcd_exit_keys(data);

	hid_set_drvdata(hdev, NULL);
	mutex_destroy(&data->mutex);
	/* Finally, clean up the picolcd data itself */
	kfree(data);
}
