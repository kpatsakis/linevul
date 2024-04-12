void PictureLayer::SetNeedsDisplayRect(const gfx::Rect& layer_rect) {
  if (!layer_rect.IsEmpty()) {
    pending_invalidation_.Union(
        gfx::IntersectRects(layer_rect, gfx::Rect(bounds())));
  }
  Layer::SetNeedsDisplayRect(layer_rect);
}
