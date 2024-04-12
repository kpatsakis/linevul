int oz_hcd_heartbeat(void *hport)
{
	int rc = 0;
	struct oz_port *port = hport;
	struct oz_hcd *ozhcd = port->ozhcd;
	struct oz_urb_link *urbl, *n;
	LIST_HEAD(xfr_list);
	struct urb *urb;
	struct oz_endpoint *ep;
	struct timespec ts, delta;

	getrawmonotonic(&ts);
	/* Check the OUT isoc endpoints to see if any URB data can be sent.
	 */
	spin_lock_bh(&ozhcd->hcd_lock);
	list_for_each_entry(ep, &port->isoc_out_ep, link) {
		if (ep->credit < 0)
			continue;
		delta = timespec_sub(ts, ep->timestamp);
		ep->credit += div_u64(timespec_to_ns(&delta), NSEC_PER_MSEC);
		if (ep->credit > ep->credit_ceiling)
			ep->credit = ep->credit_ceiling;
		ep->timestamp = ts;
		while (ep->credit && !list_empty(&ep->urb_list)) {
			urbl = list_first_entry(&ep->urb_list,
				struct oz_urb_link, link);
			urb = urbl->urb;
			if ((ep->credit + 1) < urb->number_of_packets)
				break;
			ep->credit -= urb->number_of_packets;
			if (ep->credit < 0)
				ep->credit = 0;
			list_move_tail(&urbl->link, &xfr_list);
		}
	}
	spin_unlock_bh(&ozhcd->hcd_lock);
	/* Send to PD and complete URBs.
	 */
	list_for_each_entry_safe(urbl, n, &xfr_list, link) {
		urb = urbl->urb;
		list_del_init(&urbl->link);
		urb->error_count = 0;
		urb->start_frame = oz_usb_get_frame_number();
		oz_usb_send_isoc(port->hpd, urbl->ep_num, urb);
		oz_free_urb_link(urbl);
		oz_complete_urb(port->ozhcd->hcd, urb, 0);
	}
	/* Check the IN isoc endpoints to see if any URBs can be completed.
	 */
	spin_lock_bh(&ozhcd->hcd_lock);
	list_for_each_entry(ep, &port->isoc_in_ep, link) {
		if (ep->flags & OZ_F_EP_BUFFERING) {
			if (ep->buffered_units >= OZ_IN_BUFFERING_UNITS) {
				ep->flags &= ~OZ_F_EP_BUFFERING;
				ep->credit = 0;
				ep->timestamp = ts;
				ep->start_frame = 0;
			}
			continue;
		}
		delta = timespec_sub(ts, ep->timestamp);
		ep->credit += div_u64(timespec_to_ns(&delta), NSEC_PER_MSEC);
		ep->timestamp = ts;
		list_for_each_entry_safe(urbl, n, &ep->urb_list, link) {
			struct urb *urb = urbl->urb;
			int len = 0;
			int copy_len;
			int i;

			if (ep->credit  < urb->number_of_packets)
				break;
			if (ep->buffered_units < urb->number_of_packets)
				break;
			urb->actual_length = 0;
			for (i = 0; i < urb->number_of_packets; i++) {
				len = ep->buffer[ep->out_ix];
				if (++ep->out_ix == ep->buffer_size)
					ep->out_ix = 0;
				copy_len = ep->buffer_size - ep->out_ix;
				if (copy_len > len)
					copy_len = len;
				memcpy(urb->transfer_buffer,
					&ep->buffer[ep->out_ix], copy_len);
				if (copy_len < len) {
					memcpy(urb->transfer_buffer+copy_len,
						ep->buffer, len-copy_len);
					ep->out_ix = len-copy_len;
				} else
					ep->out_ix += copy_len;
				if (ep->out_ix == ep->buffer_size)
					ep->out_ix = 0;
				urb->iso_frame_desc[i].offset =
					urb->actual_length;
				urb->actual_length += len;
				urb->iso_frame_desc[i].actual_length = len;
				urb->iso_frame_desc[i].status = 0;
			}
			ep->buffered_units -= urb->number_of_packets;
			urb->error_count = 0;
			urb->start_frame = ep->start_frame;
			ep->start_frame += urb->number_of_packets;
			list_move_tail(&urbl->link, &xfr_list);
			ep->credit -= urb->number_of_packets;
		}
	}
	if (!list_empty(&port->isoc_out_ep) || !list_empty(&port->isoc_in_ep))
		rc = 1;
	spin_unlock_bh(&ozhcd->hcd_lock);
	/* Complete the filled URBs.
	 */
	list_for_each_entry_safe(urbl, n, &xfr_list, link) {
		urb = urbl->urb;
		list_del_init(&urbl->link);
		oz_free_urb_link(urbl);
		oz_complete_urb(port->ozhcd->hcd, urb, 0);
	}
	/* Check if there are any ep0 requests that have timed out.
	 * If so resent to PD.
	 */
	ep = port->out_ep[0];
	if (ep) {
		spin_lock_bh(&ozhcd->hcd_lock);
		list_for_each_entry_safe(urbl, n, &ep->urb_list, link) {
			if (urbl->submit_counter > EP0_TIMEOUT_COUNTER) {
				oz_dbg(ON, "Request 0x%p timeout\n", urbl->urb);
				list_move_tail(&urbl->link, &xfr_list);
				urbl->submit_counter = 0;
			} else {
				urbl->submit_counter++;
			}
		}
		if (!list_empty(&ep->urb_list))
			rc = 1;
		spin_unlock_bh(&ozhcd->hcd_lock);
		list_for_each_entry_safe(urbl, n, &xfr_list, link) {
			oz_dbg(ON, "Resending request to PD\n");
			oz_process_ep0_urb(ozhcd, urbl->urb, GFP_ATOMIC);
			oz_free_urb_link(urbl);
		}
	}
	return rc;
}
