void RenderWidgetHostImpl::GetWebScreenInfo(blink::WebScreenInfo* result) {
  TRACE_EVENT0("renderer_host", "RenderWidgetHostImpl::GetWebScreenInfo");
  if (view_)
    view_->GetScreenInfo(result);
  else
    RenderWidgetHostViewBase::GetDefaultScreenInfo(result);
  latency_tracker_.set_device_scale_factor(result->deviceScaleFactor);
  if (scale_input_to_viewport_)
    input_router_->SetDeviceScaleFactor(result->deviceScaleFactor);
}
