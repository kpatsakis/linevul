void RenderViewHostImpl::SetAltErrorPageURL(const GURL& url) {
  Send(new ViewMsg_SetAltErrorPageURL(GetRoutingID(), url));
}
