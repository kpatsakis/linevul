static int dwc3_gadget_set_xfer_resource(struct dwc3 *dwc, struct dwc3_ep *dep)
{
	struct dwc3_gadget_ep_cmd_params params;

	memset(&params, 0x00, sizeof(params));

	params.param0 = DWC3_DEPXFERCFG_NUM_XFER_RES(1);

	return dwc3_send_gadget_ep_cmd(dep, DWC3_DEPCMD_SETTRANSFRESOURCE,
			&params);
}
