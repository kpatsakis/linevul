void WebContentsImpl::RenderViewDeleted(RenderViewHost* rvh) {
  FOR_EACH_OBSERVER(WebContentsObserver, observers_, RenderViewDeleted(rvh));
}
