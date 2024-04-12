void GpuProcessHost::OnAcceleratedSurfaceRelease(
    const GpuHostMsg_AcceleratedSurfaceRelease_Params& params) {
  TRACE_EVENT0("gpu", "GpuProcessHost::OnAcceleratedSurfaceRelease");

  gfx::PluginWindowHandle handle =
      GpuSurfaceTracker::Get()->GetSurfaceWindowHandle(params.surface_id);
  if (!handle) {
#if defined(USE_AURA)
    RouteOnUIThread(GpuHostMsg_AcceleratedSurfaceRelease(params));
    return;
#endif
  }

  scoped_refptr<AcceleratedPresenter> presenter(
      AcceleratedPresenter::GetForWindow(handle));
  if (!presenter)
    return;

  presenter->ReleaseSurface();
}
