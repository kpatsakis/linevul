void RenderFrameImpl::SaveImageFromDataURL(const blink::WebString& data_url) {
  if (data_url.length() < kMaxLengthOfDataURLString) {
    Send(new FrameHostMsg_SaveImageFromDataURL(render_view_->GetRoutingID(),
                                               routing_id_, data_url.Utf8()));
  }
}
