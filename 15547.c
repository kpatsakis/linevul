static int __dwc3_gadget_get_frame(struct dwc3 *dwc)
{
	u32			reg;

	reg = dwc3_readl(dwc->regs, DWC3_DSTS);
	return DWC3_DSTS_SOFFN(reg);
}
