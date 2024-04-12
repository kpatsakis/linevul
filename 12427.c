void RenderFrameImpl::PepperCancelComposition(
    PepperPluginInstanceImpl* instance) {
  if (instance != focused_pepper_plugin_)
    return;
  Send(new InputHostMsg_ImeCancelComposition(render_view_->GetRoutingID()));
#if defined(OS_MACOSX) || defined(USE_AURA)
  GetRenderWidget()->UpdateCompositionInfo(
      false /* not an immediate request */);
#endif
}
