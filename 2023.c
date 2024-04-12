bool RenderWidgetHostImpl::TryGetBackingStore(const gfx::Size& desired_size,
                                              BackingStore** backing_store) {
  if (view_->HasAcceleratedSurface(desired_size)) {
    *backing_store = NULL;
    return true;
  }

  *backing_store = BackingStoreManager::GetBackingStore(this, desired_size);
  return !!*backing_store;
}
