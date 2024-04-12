void WebContentsImpl::UpdateDeviceScaleFactor(double device_scale_factor) {
  SendPageMessage(
      new PageMsg_SetDeviceScaleFactor(MSG_ROUTING_NONE, device_scale_factor));
}
