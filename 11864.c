void WebGraphicsContext3DCommandBufferImpl::deleteShader(WebGLId shader) {
  gl_->DeleteShader(shader);
}
