void WebContentsImpl::Find(int request_id,
                           const base::string16& search_text,
                           const blink::WebFindOptions& options) {
  if (search_text.empty()) {
    NOTREACHED();
    return;
  }

  if (browser_plugin_embedder_ &&
      browser_plugin_embedder_->Find(request_id, search_text, options)) {
    return;
  }
  GetMainFrame()->Send(new FrameMsg_Find(GetMainFrame()->GetRoutingID(),
                                         request_id, search_text, options));
}
