gfx::Size GpuCommandBufferStub::GetSurfaceSize() const {
  if (!surface_)
    return gfx::Size();
  return surface_->GetSize();
}
