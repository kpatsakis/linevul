static void dwc3_stop_active_transfer(struct dwc3 *dwc, u32 epnum, bool force)
{
	struct dwc3_ep *dep;
	struct dwc3_gadget_ep_cmd_params params;
	u32 cmd;
	int ret;

	dep = dwc->eps[epnum];

	if ((dep->flags & DWC3_EP_END_TRANSFER_PENDING) ||
	    !dep->resource_index)
		return;

	/*
	 * NOTICE: We are violating what the Databook says about the
	 * EndTransfer command. Ideally we would _always_ wait for the
	 * EndTransfer Command Completion IRQ, but that's causing too
	 * much trouble synchronizing between us and gadget driver.
	 *
	 * We have discussed this with the IP Provider and it was
	 * suggested to giveback all requests here, but give HW some
	 * extra time to synchronize with the interconnect. We're using
	 * an arbitrary 100us delay for that.
	 *
	 * Note also that a similar handling was tested by Synopsys
	 * (thanks a lot Paul) and nothing bad has come out of it.
	 * In short, what we're doing is:
	 *
	 * - Issue EndTransfer WITH CMDIOC bit set
	 * - Wait 100us
	 *
	 * As of IP version 3.10a of the DWC_usb3 IP, the controller
	 * supports a mode to work around the above limitation. The
	 * software can poll the CMDACT bit in the DEPCMD register
	 * after issuing a EndTransfer command. This mode is enabled
	 * by writing GUCTL2[14]. This polling is already done in the
	 * dwc3_send_gadget_ep_cmd() function so if the mode is
	 * enabled, the EndTransfer command will have completed upon
	 * returning from this function and we don't need to delay for
	 * 100us.
	 *
	 * This mode is NOT available on the DWC_usb31 IP.
	 */

	cmd = DWC3_DEPCMD_ENDTRANSFER;
	cmd |= force ? DWC3_DEPCMD_HIPRI_FORCERM : 0;
	cmd |= DWC3_DEPCMD_CMDIOC;
	cmd |= DWC3_DEPCMD_PARAM(dep->resource_index);
	memset(&params, 0, sizeof(params));
	ret = dwc3_send_gadget_ep_cmd(dep, cmd, &params);
	WARN_ON_ONCE(ret);
	dep->resource_index = 0;
	dep->flags &= ~DWC3_EP_BUSY;

	if (dwc3_is_usb31(dwc) || dwc->revision < DWC3_REVISION_310A) {
		dep->flags |= DWC3_EP_END_TRANSFER_PENDING;
		udelay(100);
	}
}
