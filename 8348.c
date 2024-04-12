static int pegasus_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct pegasus *pegasus = usb_get_intfdata(intf);

	netif_device_detach(pegasus->net);
	cancel_delayed_work(&pegasus->carrier_check);
	if (netif_running(pegasus->net)) {
		usb_kill_urb(pegasus->rx_urb);
		usb_kill_urb(pegasus->intr_urb);
	}
	return 0;
}
