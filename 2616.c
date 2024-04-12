void WebContentsImpl::RequestFindMatchRects(int current_version) {
  GetOrCreateFindRequestManager()->RequestFindMatchRects(current_version);
}
