void WebGraphicsContext3DCommandBufferImpl::vertexAttribPointer(
    WGC3Duint index, WGC3Dint size, WGC3Denum type, WGC3Dboolean normalized,
    WGC3Dsizei stride, WGC3Dintptr offset) {
  gl_->VertexAttribPointer(
      index, size, type, normalized, stride,
      reinterpret_cast<void*>(static_cast<intptr_t>(offset)));
}
