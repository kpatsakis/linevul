void PaintController::InvalidateAllInternal() {
  DCHECK(new_display_item_list_.IsEmpty());
  current_paint_artifact_.Reset();
  current_cache_generation_.Invalidate();
}
