ScopedTextureBinder::ScopedTextureBinder(ContextState* state,
                                         GLuint id,
                                         GLenum target)
    : state_(state),
      target_(target) {
  ScopedGLErrorSuppressor suppressor(
      "ScopedTextureBinder::ctor", state_->GetErrorState());

  auto* api = state->api();
  api->glActiveTextureFn(GL_TEXTURE0);
  api->glBindTextureFn(target, id);
}
