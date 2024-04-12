void RenderFrameImpl::WasHidden() {
  for (auto& observer : observers_)
    observer.WasHidden();

#if BUILDFLAG(ENABLE_PLUGINS)
  for (auto* plugin : active_pepper_instances_)
    plugin->PageVisibilityChanged(false);
#endif  // ENABLE_PLUGINS

  if (GetWebFrame()->FrameWidget()) {
    GetWebFrame()->FrameWidget()->SetVisibilityState(VisibilityState());
  }
}
