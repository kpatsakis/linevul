void RenderViewImpl::PpapiPluginCancelComposition() {
  Send(new ViewHostMsg_ImeCancelComposition(routing_id()));
  const ui::Range range(ui::Range::InvalidRange());
  const std::vector<gfx::Rect> empty_bounds;
  UpdateCompositionInfo(range, empty_bounds);
}
