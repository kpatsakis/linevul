void RenderWidgetHostImpl::OnSnapshotDataReceived(int snapshot_id,
                                                  const unsigned char* data,
                                                  size_t size) {
  PendingSnapshotMap::iterator it = pending_browser_snapshots_.begin();
  while (it != pending_browser_snapshots_.end()) {
      if (it->first <= snapshot_id) {
        it->second.Run(data, size);
        pending_browser_snapshots_.erase(it++);
      } else {
        ++it;
      }
  }
}
