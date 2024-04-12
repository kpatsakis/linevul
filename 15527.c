void ChromeClientImpl::SetTouchAction(LocalFrame* frame,
                                      TouchAction touch_action) {
  DCHECK(frame);
  WebLocalFrameImpl* web_frame = WebLocalFrameImpl::FromFrame(frame);
  WebFrameWidgetBase* widget = web_frame->LocalRoot()->FrameWidget();
  if (!widget)
    return;

  if (WebWidgetClient* client = widget->Client())
    client->SetTouchAction(static_cast<TouchAction>(touch_action));
}
