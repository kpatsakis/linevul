error::Error GLES2DecoderPassthroughImpl::DoEndSharedImageAccessDirectCHROMIUM(
    GLuint client_id) {
  auto found = resources_->texture_shared_image_map.find(client_id);
  if (found == resources_->texture_shared_image_map.end()) {
    InsertError(GL_INVALID_OPERATION, "texture is not a shared image");
    return error::kNoError;
  }

  SharedImageRepresentationGLTexturePassthrough* shared_image =
      found->second.get();
  shared_image->EndAccess();
  return error::kNoError;
}
