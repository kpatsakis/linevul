void RenderViewImpl::CreatedPluginWindow(gfx::PluginWindowHandle window) {
#if defined(USE_X11)
  Send(new ViewHostMsg_CreatePluginContainer(routing_id(), window));
#endif
}
