void GuestViewBase::GuestSizeChanged(const gfx::Size& new_size) {
  if (!auto_size_enabled_)
    return;
  GuestSizeChangedDueToAutoSize(guest_size_, new_size);
  DispatchOnResizeEvent(guest_size_, new_size);
  guest_size_ = new_size;
}
