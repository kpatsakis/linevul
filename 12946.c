WebPluginAcceleratedSurface* WebPluginProxy::GetAcceleratedSurface(
    gfx::GpuPreference gpu_preference) {
  if (!accelerated_surface_.get())
    accelerated_surface_.reset(
        WebPluginAcceleratedSurfaceProxy::Create(this, gpu_preference));
  return accelerated_surface_.get();
}
