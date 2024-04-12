DXVAVideoDecodeAccelerator::PendingSampleInfo::PendingSampleInfo(
    int32 buffer_id, IDirect3DSurface9* surface)
    : input_buffer_id(buffer_id),
      dest_surface(surface) {
}
