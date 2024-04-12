blink::WebPlugin* RenderFrameImpl::GetWebPluginForFind() {
  if (frame_->GetDocument().IsPluginDocument())
    return frame_->GetDocument().To<WebPluginDocument>().Plugin();

#if BUILDFLAG(ENABLE_PLUGINS)
  if (plugin_find_handler_)
    return plugin_find_handler_->container()->Plugin();
#endif

  return nullptr;
}
