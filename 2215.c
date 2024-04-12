void WebContentsImpl::DidFinishNavigation(NavigationHandle* navigation_handle) {
  FOR_EACH_OBSERVER(WebContentsObserver, observers_,
                    DidFinishNavigation(navigation_handle));
}
