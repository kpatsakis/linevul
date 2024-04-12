void WebContentsImpl::UpdateRenderViewSizeForRenderManager(bool is_main_frame) {
  gfx::Size size = GetSizeForNewRenderView(is_main_frame);
  if (!size.IsEmpty())
    view_->SizeContents(size);
}
