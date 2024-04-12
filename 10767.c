void RenderWidgetHostViewAura::OnSetNeedsFlushInput() {
  needs_flush_input_ = true;
  UpdateNeedsBeginFramesInternal();
}
