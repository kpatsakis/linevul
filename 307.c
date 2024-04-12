void RenderFrameImpl::BindToFrame(WebLocalFrame* web_frame) {
  DCHECK(!frame_);

  std::pair<FrameMap::iterator, bool> result =
      g_frame_map.Get().emplace(web_frame, this);
  CHECK(result.second) << "Inserting a duplicate item.";

  frame_ = web_frame;
}
