void RenderViewImpl::OnSetDeviceScaleFactor(float device_scale_factor) {
  RenderWidget::OnSetDeviceScaleFactor(device_scale_factor);
  if (webview())
    webview()->setDeviceScaleFactor(device_scale_factor);
}
