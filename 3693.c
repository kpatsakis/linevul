static void magicmouse_input_configured(struct hid_device *hdev,
		struct hid_input *hi)

{
	struct magicmouse_sc *msc = hid_get_drvdata(hdev);

	int ret = magicmouse_setup_input(msc->input, hdev);
	if (ret) {
		hid_err(hdev, "magicmouse setup input failed (%d)\n", ret);
		/* clean msc->input to notify probe() of the failure */
		msc->input = NULL;
	}
}
