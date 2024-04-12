void WebGLRenderingContextBase::DrawElementsInstancedANGLE(GLenum mode,
                                                           GLsizei count,
                                                           GLenum type,
                                                           long long offset,
                                                           GLsizei primcount) {
  if (!ValidateDrawElements("drawElementsInstancedANGLE", type, offset))
    return;

  if (!bound_vertex_array_object_->IsAllEnabledAttribBufferBound()) {
    SynthesizeGLError(GL_INVALID_OPERATION, "drawElementsInstancedANGLE",
                      "no buffer is bound to enabled attribute");
    return;
  }

  ScopedRGBEmulationColorMask emulation_color_mask(this, color_mask_,
                                                   drawing_buffer_.get());
  ClearIfComposited();
  ContextGL()->DrawElementsInstancedANGLE(
      mode, count, type, reinterpret_cast<void*>(static_cast<intptr_t>(offset)),
      primcount);
  MarkContextChanged(kCanvasChanged);
}
