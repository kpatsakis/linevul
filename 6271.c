bool RenderWidgetHostImpl::PaintBackingStoreRect(
    TransportDIB::Id bitmap,
    const gfx::Rect& bitmap_rect,
    const std::vector<gfx::Rect>& copy_rects,
    const gfx::Size& view_size,
    float scale_factor,
    const base::Closure& completion_callback) {
  if (!view_)
    return false;

  if (is_hidden_) {
    needs_repainting_on_restore_ = true;
    return false;
  }

  bool needs_full_paint = false;
  bool scheduled_completion_callback = false;
  BackingStoreManager::PrepareBackingStore(this, view_size, bitmap, bitmap_rect,
                                           copy_rects, scale_factor,
                                           completion_callback,
                                           &needs_full_paint,
                                           &scheduled_completion_callback);
  if (needs_full_paint) {
    repaint_start_time_ = TimeTicks::Now();
    repaint_ack_pending_ = true;
    Send(new ViewMsg_Repaint(routing_id_, view_size));
  }

  return scheduled_completion_callback;
}
