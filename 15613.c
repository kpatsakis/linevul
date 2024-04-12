void RenderFrameImpl::didLoadResourceFromMemoryCache(
    blink::WebLocalFrame* frame,
    const blink::WebURLRequest& request,
    const blink::WebURLResponse& response) {
  DCHECK(!frame_ || frame_ == frame);
  GURL url(request.url());
  if (url.SchemeIs(url::kDataScheme))
    return;

  render_view_->Send(new ViewHostMsg_DidLoadResourceFromMemoryCache(
      render_view_->GetRoutingID(),
      url,
      response.securityInfo(),
      request.httpMethod().utf8(),
      response.mimeType().utf8(),
      WebURLRequestToResourceType(request)));
}
