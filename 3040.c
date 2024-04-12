void LayerTreeHostImpl::DidDrawAllLayers(const FrameData& frame) {
  for (size_t i = 0; i < frame.will_draw_layers.size(); ++i)
    frame.will_draw_layers[i]->DidDraw(resource_provider_.get());

  for (auto* it : video_frame_controllers_)
    it->DidDrawFrame();
}
