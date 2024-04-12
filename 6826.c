void GLES2DecoderImpl::DoScheduleCALayerInUseQueryCHROMIUM(
    GLsizei count,
    const volatile GLuint* textures) {
  std::vector<gl::GLSurface::CALayerInUseQuery> queries;
  queries.reserve(count);
  for (GLsizei i = 0; i < count; ++i) {
    gl::GLImage* image = nullptr;
    GLuint texture_id = textures[i];
    if (texture_id) {
      TextureRef* ref = texture_manager()->GetTexture(texture_id);
      if (!ref) {
        LOCAL_SET_GL_ERROR(GL_INVALID_VALUE,
                           "glScheduleCALayerInUseQueryCHROMIUM",
                           "unknown texture");
        return;
      }
      Texture::ImageState image_state;
      image = ref->texture()->GetLevelImage(ref->texture()->target(), 0,
                                            &image_state);
    }
    gl::GLSurface::CALayerInUseQuery query;
    query.image = image;
    query.texture = texture_id;
    queries.push_back(query);
  }

  surface_->ScheduleCALayerInUseQuery(std::move(queries));
}
