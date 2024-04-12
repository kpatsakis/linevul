void RenderViewImpl::OnUpdateScreenInfo(const ScreenInfo& screen_info) {
  if (!main_render_frame_)
    screen_info_ = screen_info;
}
