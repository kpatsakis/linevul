void SiteInstanceImpl::RenderProcessWillExit(RenderProcessHost* host) {
  for (auto& observer : observers_)
    observer.RenderProcessGone(this);
}
