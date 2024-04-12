void RenderViewHostImpl::NotifyTimezoneChange() {
  Send(new ViewMsg_TimezoneChange(GetRoutingID()));
}
