WebPluginProxy::~WebPluginProxy() {
#if defined(USE_X11)
  if (windowless_shm_pixmaps_[0] != None)
    XFreePixmap(ui::GetXDisplay(), windowless_shm_pixmaps_[0]);
  if (windowless_shm_pixmaps_[1] != None)
    XFreePixmap(ui::GetXDisplay(), windowless_shm_pixmaps_[1]);
#endif

#if defined(OS_MACOSX)
  if (accelerated_surface_.get())
    accelerated_surface_.reset();
#endif

  if (plugin_element_)
    WebBindings::releaseObject(plugin_element_);
  if (window_npobject_)
    WebBindings::releaseObject(window_npobject_);
}
