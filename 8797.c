void Layer::CalculateContentsScale(
    float ideal_contents_scale,
    float device_scale_factor,
    float page_scale_factor,
    bool animating_transform_to_screen,
    float* contents_scale_x,
    float* contents_scale_y,
    gfx::Size* content_bounds) {
  DCHECK(layer_tree_host_);

  *contents_scale_x = 1;
  *contents_scale_y = 1;
  *content_bounds = bounds();
}
