WebKit::WebPlugin* RenderViewImpl::CreatePlugin(
    WebKit::WebFrame* frame,
    const webkit::WebPluginInfo& info,
    const WebKit::WebPluginParams& params) {
  bool pepper_plugin_was_registered = false;
  scoped_refptr<webkit::ppapi::PluginModule> pepper_module(
      pepper_delegate_.CreatePepperPluginModule(info,
                                                &pepper_plugin_was_registered));
  if (pepper_plugin_was_registered) {
    if (!pepper_module)
      return NULL;
    return new webkit::ppapi::WebPluginImpl(
        pepper_module.get(), params, pepper_delegate_.AsWeakPtr());
  }

#if defined(USE_AURA)
  return NULL;
#else
  return new webkit::npapi::WebPluginImpl(
      frame, params, info.path, AsWeakPtr());
#endif
}
