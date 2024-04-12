error::Error GLES2DecoderImpl::HandleTexSubImage2D(
    uint32 immediate_data_size, const gles2::TexSubImage2D& c) {
  TRACE_EVENT0("gpu", "GLES2DecoderImpl::HandleTexSubImage2D");
  GLboolean internal = static_cast<GLboolean>(c.internal);
  if (internal == GL_TRUE && tex_image_2d_failed_)
    return error::kNoError;

  GLenum target = static_cast<GLenum>(c.target);
  GLint level = static_cast<GLint>(c.level);
  GLint xoffset = static_cast<GLint>(c.xoffset);
  GLint yoffset = static_cast<GLint>(c.yoffset);
  GLsizei width = static_cast<GLsizei>(c.width);
  GLsizei height = static_cast<GLsizei>(c.height);
  GLenum format = static_cast<GLenum>(c.format);
  GLenum type = static_cast<GLenum>(c.type);
  uint32 data_size;
  if (!GLES2Util::ComputeImageDataSizes(
      width, height, format, type, unpack_alignment_, &data_size, NULL, NULL)) {
    return error::kOutOfBounds;
  }
  const void* pixels = GetSharedMemoryAs<const void*>(
      c.pixels_shm_id, c.pixels_shm_offset, data_size);
  if (!validators_->texture_target.IsValid(target)) {
    SetGLErrorInvalidEnum("glTexSubImage2D", target, "target");
    return error::kNoError;
  }
  if (width < 0) {
    SetGLError(GL_INVALID_VALUE, "glTexSubImage2D", "width < 0");
    return error::kNoError;
  }
  if (height < 0) {
    SetGLError(GL_INVALID_VALUE, "glTexSubImage2D", "height < 0");
    return error::kNoError;
  }
  if (!validators_->texture_format.IsValid(format)) {
    SetGLErrorInvalidEnum("glTexSubImage2D", format, "format");
    return error::kNoError;
  }
  if (!validators_->pixel_type.IsValid(type)) {
    SetGLErrorInvalidEnum("glTexSubImage2D", type, "type");
    return error::kNoError;
  }
  if (pixels == NULL) {
    return error::kOutOfBounds;
  }
  DoTexSubImage2D(
      target, level, xoffset, yoffset, width, height, format, type, pixels);
  return error::kNoError;
}
