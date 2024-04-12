WebPluginAcceleratedSurfaceProxy::WebPluginAcceleratedSurfaceProxy(
    WebPluginProxy* plugin_proxy)
        : plugin_proxy_(plugin_proxy),
          window_handle_(NULL) {
  surface_ = new AcceleratedSurface;
  if (!surface_->Initialize(NULL, true)) {
    delete surface_;
    surface_ = NULL;
    return;
  }

  surface_->SetTransportDIBAllocAndFree(
      NewCallback(plugin_proxy_, &WebPluginProxy::AllocSurfaceDIB),
      NewCallback(plugin_proxy_, &WebPluginProxy::FreeSurfaceDIB));
}
