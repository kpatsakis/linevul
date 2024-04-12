static void dwc3_suspend_gadget(struct dwc3 *dwc)
{
	if (dwc->gadget_driver && dwc->gadget_driver->suspend) {
		spin_unlock(&dwc->lock);
		dwc->gadget_driver->suspend(&dwc->gadget);
		spin_lock(&dwc->lock);
	}
}
