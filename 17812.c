gfx::GLSurfaceHandle RenderWidgetHostViewGtk::GetCompositingSurface() {
  if (compositing_surface_ == gfx::kNullPluginWindow) {
    GtkNativeViewManager* manager = GtkNativeViewManager::GetInstance();
    gfx::NativeViewId view_id = GetNativeViewId();

    if (!manager->GetPermanentXIDForId(&compositing_surface_, view_id)) {
      DLOG(ERROR) << "Can't find XID for view id " << view_id;
    }
  }
  return gfx::GLSurfaceHandle(compositing_surface_, true);
}
