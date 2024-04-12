void WebContentsImpl::OnPepperInstanceCreated() {
  FOR_EACH_OBSERVER(WebContentsObserver, observers_, PepperInstanceCreated());
}
