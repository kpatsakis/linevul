void RenderFrameImpl::DownloadURL(const blink::WebURLRequest& request,
                                  const blink::WebString& suggested_name) {
  FrameHostMsg_DownloadUrl_Params params;
  params.render_view_id = render_view_->GetRoutingID();
  params.render_frame_id = GetRoutingID();
  params.url = request.Url();
  params.referrer = RenderViewImpl::GetReferrerFromRequest(frame_, request);
  params.initiator_origin = request.RequestorOrigin();
  params.suggested_name = suggested_name.Utf16();

  Send(new FrameHostMsg_DownloadUrl(params));
}
