void GLES2DecoderImpl::ReleaseIOSurfaceForTexture(GLuint texture_id) {
  TextureToIOSurfaceMap::iterator it = texture_to_io_surface_map_.find(
      texture_id);
  if (it != texture_to_io_surface_map_.end()) {
    CFTypeRef surface = it->second;
    CFRelease(surface);
    texture_to_io_surface_map_.erase(it);
  }
}
