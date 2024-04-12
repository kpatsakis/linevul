void RenderViewImpl::registerProtocolHandler(const WebString& scheme,
                                             const WebString& base_url,
                                             const WebString& url,
                                             const WebString& title) {
  GURL base(base_url);
  GURL absolute_url = base.Resolve(UTF16ToUTF8(url));
  if (base.GetOrigin() != absolute_url.GetOrigin()) {
    return;
  }
  Send(new ViewHostMsg_RegisterProtocolHandler(routing_id_,
                                               UTF16ToUTF8(scheme),
                                               absolute_url,
                                               title));
}
