static int __dwc3_gadget_ep_queue(struct dwc3_ep *dep, struct dwc3_request *req)
{
	struct dwc3		*dwc = dep->dwc;

	if (!dep->endpoint.desc) {
		dev_err(dwc->dev, "%s: can't queue to disabled endpoint\n",
				dep->name);
		return -ESHUTDOWN;
	}

	if (WARN(req->dep != dep, "request %pK belongs to '%s'\n",
				&req->request, req->dep->name))
		return -EINVAL;

	pm_runtime_get(dwc->dev);

	req->request.actual	= 0;
	req->request.status	= -EINPROGRESS;
	req->direction		= dep->direction;
	req->epnum		= dep->number;

	trace_dwc3_ep_queue(req);

	list_add_tail(&req->list, &dep->pending_list);

	/*
	 * NOTICE: Isochronous endpoints should NEVER be prestarted. We must
	 * wait for a XferNotReady event so we will know what's the current
	 * (micro-)frame number.
	 *
	 * Without this trick, we are very, very likely gonna get Bus Expiry
	 * errors which will force us issue EndTransfer command.
	 */
	if (usb_endpoint_xfer_isoc(dep->endpoint.desc)) {
		if ((dep->flags & DWC3_EP_PENDING_REQUEST)) {
			if (dep->flags & DWC3_EP_TRANSFER_STARTED) {
				dwc3_stop_active_transfer(dwc, dep->number, true);
				dep->flags = DWC3_EP_ENABLED;
			} else {
				u32 cur_uf;

				cur_uf = __dwc3_gadget_get_frame(dwc);
				__dwc3_gadget_start_isoc(dwc, dep, cur_uf);
				dep->flags &= ~DWC3_EP_PENDING_REQUEST;
			}
			return 0;
		}

		if ((dep->flags & DWC3_EP_BUSY) &&
		    !(dep->flags & DWC3_EP_MISSED_ISOC))
			goto out;

		return 0;
	}

out:
	return __dwc3_gadget_kick_transfer(dep);
}
