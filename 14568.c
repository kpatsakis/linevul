void RenderFrameImpl::OnCopyImageAt(int x, int y) {
  blink::WebFloatRect viewport_position(x, y, 0, 0);
  GetLocalRootRenderWidget()->ConvertWindowToViewport(&viewport_position);
  frame_->CopyImageAt(WebPoint(viewport_position.x, viewport_position.y));
}
