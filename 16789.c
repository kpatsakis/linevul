PaintArtifactCompositor::ScrollHitTestLayerForPendingLayer(
    const PaintArtifact& paint_artifact,
    const PendingLayer& pending_layer,
    gfx::Vector2dF& layer_offset) {
  const auto* scroll_offset_node =
      ScrollTranslationForScrollHitTestLayer(paint_artifact, pending_layer);
  if (!scroll_offset_node)
    return nullptr;

  const auto& scroll_node = *scroll_offset_node->ScrollNode();
  auto scroll_element_id = scroll_node.GetCompositorElementId();

  scoped_refptr<cc::Layer> scroll_layer;
  for (auto& existing_layer : scroll_hit_test_layers_) {
    if (existing_layer && existing_layer->element_id() == scroll_element_id)
      scroll_layer = existing_layer;
  }
  if (!scroll_layer) {
    scroll_layer = cc::Layer::Create();
    scroll_layer->SetElementId(scroll_element_id);
  }

  auto offset = scroll_node.ContainerRect().Location();
  layer_offset = gfx::Vector2dF(offset.X(), offset.Y());
  auto bounds = scroll_node.ContainerRect().Size();
  scroll_layer->SetScrollable(static_cast<gfx::Size>(bounds));
  scroll_layer->SetBounds(static_cast<gfx::Size>(bounds));
  scroll_layer->set_did_scroll_callback(scroll_callback_);
  return scroll_layer;
}
