void RenderThreadImpl::OnMemoryPressure(
    base::MemoryPressureListener::MemoryPressureLevel memory_pressure_level) {
  base::allocator::ReleaseFreeMemory();

  if (webkit_platform_support_ && blink::mainThreadIsolate()) {
    blink::mainThreadIsolate()->LowMemoryNotification();
  }

  if (memory_pressure_level ==
      base::MemoryPressureListener::MEMORY_PRESSURE_CRITICAL) {
    if (webkit_platform_support_) {
      blink::WebImageCache::clear();
    }

    size_t font_cache_limit = SkGraphics::SetFontCacheLimit(0);
    SkGraphics::SetFontCacheLimit(font_cache_limit);
  }
}
