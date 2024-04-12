void WebContentsImpl::OnFirstVisuallyNonEmptyPaint(int32 page_id) {
  FOR_EACH_OBSERVER(WebContentsObserver, observers_,
                    DidFirstVisuallyNonEmptyPaint(page_id));
}
