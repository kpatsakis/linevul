void RenderWidgetHostImpl::OnSnapshotFromSurfaceReceived(
    int snapshot_id,
    int retry_count,
    const SkBitmap& bitmap) {
  static constexpr int kMaxRetries = 5;
  if (bitmap.drawsNothing() && retry_count < kMaxRetries) {
    GetView()->CopyFromSurface(
        gfx::Rect(), gfx::Size(),
        base::BindOnce(&RenderWidgetHostImpl::OnSnapshotFromSurfaceReceived,
                       weak_factory_.GetWeakPtr(), snapshot_id,
                       retry_count + 1));
    return;
  }
  gfx::Image image;
  if (!bitmap.drawsNothing())
    image = gfx::Image::CreateFrom1xBitmap(bitmap);
  PendingSnapshotMap::iterator it = pending_surface_browser_snapshots_.begin();
  while (it != pending_surface_browser_snapshots_.end()) {
    if (it->first <= snapshot_id) {
      it->second.Run(image);
      pending_surface_browser_snapshots_.erase(it++);
    } else {
      ++it;
    }
  }
}
