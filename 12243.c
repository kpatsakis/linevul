static void rx_fixup(unsigned long data)
{
	pegasus_t *pegasus;
	int status;

	pegasus = (pegasus_t *) data;
	if (pegasus->flags & PEGASUS_UNPLUG)
		return;

	if (pegasus->flags & PEGASUS_RX_URB_FAIL)
		if (pegasus->rx_skb)
			goto try_again;
	if (pegasus->rx_skb == NULL)
		pegasus->rx_skb = __netdev_alloc_skb_ip_align(pegasus->net,
							      PEGASUS_MTU,
							      GFP_ATOMIC);
	if (pegasus->rx_skb == NULL) {
		netif_warn(pegasus, rx_err, pegasus->net, "low on memory\n");
		tasklet_schedule(&pegasus->rx_tl);
		return;
	}
	usb_fill_bulk_urb(pegasus->rx_urb, pegasus->usb,
			  usb_rcvbulkpipe(pegasus->usb, 1),
			  pegasus->rx_skb->data, PEGASUS_MTU,
			  read_bulk_callback, pegasus);
try_again:
	status = usb_submit_urb(pegasus->rx_urb, GFP_ATOMIC);
	if (status == -ENODEV)
		netif_device_detach(pegasus->net);
	else if (status) {
		pegasus->flags |= PEGASUS_RX_URB_FAIL;
		tasklet_schedule(&pegasus->rx_tl);
	} else {
		pegasus->flags &= ~PEGASUS_RX_URB_FAIL;
	}
}
