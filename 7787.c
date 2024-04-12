void WebContentsImpl::NotifyWebContentsLostFocus() {
  for (auto& observer : observers_)
    observer.OnWebContentsLostFocus();
}
