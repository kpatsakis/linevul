void usbhid_init_reports(struct hid_device *hid)
{
	struct hid_report *report;
	struct usbhid_device *usbhid = hid->driver_data;
	struct hid_report_enum *report_enum;
	int err, ret;

	report_enum = &hid->report_enum[HID_INPUT_REPORT];
	list_for_each_entry(report, &report_enum->report_list, list)
		usbhid_submit_report(hid, report, USB_DIR_IN);

	report_enum = &hid->report_enum[HID_FEATURE_REPORT];
	list_for_each_entry(report, &report_enum->report_list, list)
		usbhid_submit_report(hid, report, USB_DIR_IN);

	err = 0;
	ret = usbhid_wait_io(hid);
	while (ret) {
		err |= ret;
		if (test_bit(HID_CTRL_RUNNING, &usbhid->iofl))
			usb_kill_urb(usbhid->urbctrl);
		if (test_bit(HID_OUT_RUNNING, &usbhid->iofl))
			usb_kill_urb(usbhid->urbout);
		ret = usbhid_wait_io(hid);
	}

	if (err)
		hid_warn(hid, "timeout initializing reports\n");
}
