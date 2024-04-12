void RenderViewHostImpl::ExecuteMediaPlayerActionAtLocation(
  const gfx::Point& location, const WebKit::WebMediaPlayerAction& action) {
  Send(new ViewMsg_MediaPlayerActionAt(GetRoutingID(), location, action));
}
