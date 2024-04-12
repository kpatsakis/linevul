WebDevToolsAgent* WebPluginImpl::GetDevToolsAgent() {
  if (!webframe_)
    return NULL;
  WebView* view = webframe_->view();
  if (!view)
    return NULL;
  return view->devToolsAgent();
}
