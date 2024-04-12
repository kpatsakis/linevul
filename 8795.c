PaintLayerScrollableArea::PreventRelayoutScope::PreventRelayoutScope(
    SubtreeLayoutScope& layout_scope) {
  if (!count_) {
    DCHECK(!layout_scope_);
    DCHECK(NeedsRelayoutList().IsEmpty());
    layout_scope_ = &layout_scope;
  }
  count_++;
}
