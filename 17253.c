void VaapiWrapper::DestroyUnownedSurface(VASurfaceID va_surface_id) {
  base::AutoLock auto_lock(*va_lock_);

  VAStatus va_res = vaDestroySurfaces(va_display_, &va_surface_id, 1);
  VA_LOG_ON_ERROR(va_res, "vaDestroySurfaces on surface failed");
}
