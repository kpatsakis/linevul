bool LayerTreeHost::PaintContent(const LayerList& update_layer_list,
                                 bool* content_is_suitable_for_gpu) {
  base::AutoReset<bool> painting(&in_paint_layer_contents_, true);
  bool did_paint_content = false;
  for (const auto& layer : update_layer_list) {
    did_paint_content |= layer->Update();
    *content_is_suitable_for_gpu &= layer->IsSuitableForGpuRasterization();
  }
  return did_paint_content;
}
