void ChromeClientImpl::SetNeedsLowLatencyInput(LocalFrame* frame,
                                               bool needs_low_latency) {
  DCHECK(frame);
  WebLocalFrameImpl* web_frame = WebLocalFrameImpl::FromFrame(frame);
  WebFrameWidgetBase* widget = web_frame->LocalRoot()->FrameWidget();
  if (!widget)
    return;

  if (WebWidgetClient* client = widget->Client())
    client->SetNeedsLowLatencyInput(needs_low_latency);
}
