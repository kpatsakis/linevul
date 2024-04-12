gfx::Vector2d Layer::MaxScrollOffset() const {
  if (scroll_clip_layer_id_ == INVALID_ID)
    return gfx::Vector2d();

  gfx::Size scaled_scroll_bounds(bounds());
  Layer const* current_layer = this;
  Layer const* page_scale_layer = layer_tree_host()->page_scale_layer();
  float scale_factor = 1.f;
  do {
    if (current_layer == page_scale_layer) {
      scale_factor = layer_tree_host()->page_scale_factor();
      scaled_scroll_bounds.SetSize(
          scale_factor * scaled_scroll_bounds.width(),
          scale_factor * scaled_scroll_bounds.height());
    }
    current_layer = current_layer->parent();
  } while (current_layer && current_layer->id() != scroll_clip_layer_id_);
  DCHECK(current_layer);
  DCHECK(current_layer->id() == scroll_clip_layer_id_);

  gfx::Vector2dF max_offset(
      scaled_scroll_bounds.width() - current_layer->bounds().width(),
      scaled_scroll_bounds.height() - current_layer->bounds().height());
  max_offset.Scale(1.f / scale_factor);
  max_offset.SetToMax(gfx::Vector2dF());
  return gfx::ToFlooredVector2d(max_offset);
}
