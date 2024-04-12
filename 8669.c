void RenderFrameImpl::PepperCaretPositionChanged(
    PepperPluginInstanceImpl* instance) {
  if (instance != focused_pepper_plugin_)
    return;
  GetLocalRootRenderWidget()->UpdateSelectionBounds();
}
