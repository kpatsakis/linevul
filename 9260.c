ScopedTextureBinder::ScopedTextureBinder(ContextState* state,
                                         GLuint id,
                                         GLenum target)
    : state_(state),
      target_(target) {
  ScopedGLErrorSuppressor suppressor(
      "ScopedTextureBinder::ctor", state_->GetErrorState());

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(target, id);
}
