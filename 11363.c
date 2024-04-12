void GLES2DecoderImpl::RestoreCurrentRenderbufferBindings() {
  glBindRenderbufferEXT(
      GL_RENDERBUFFER,
      bound_renderbuffer_ ? bound_renderbuffer_->service_id() : 0);
}
