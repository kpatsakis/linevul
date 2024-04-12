void WebContentsImpl::AddDestructionObserver(WebContentsImpl* web_contents) {
  if (!ContainsKey(destruction_observers_, web_contents)) {
    destruction_observers_[web_contents] =
        std::make_unique<DestructionObserver>(this, web_contents);
  }
}
