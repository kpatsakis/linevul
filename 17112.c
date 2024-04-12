error::Error GLES2DecoderImpl::HandleCompressedTexImage3DBucket(
    uint32_t immediate_data_size, const volatile void* cmd_data) {
  if (!feature_info_->IsWebGL2OrES3Context())
    return error::kUnknownCommand;
  const volatile gles2::cmds::CompressedTexImage3DBucket& c =
      *static_cast<const volatile gles2::cmds::CompressedTexImage3DBucket*>(
          cmd_data);
  GLenum target = static_cast<GLenum>(c.target);
  GLint level = static_cast<GLint>(c.level);
  GLenum internal_format = static_cast<GLenum>(c.internalformat);
  GLsizei width = static_cast<GLsizei>(c.width);
  GLsizei height = static_cast<GLsizei>(c.height);
  GLsizei depth = static_cast<GLsizei>(c.depth);
  GLuint bucket_id = static_cast<GLuint>(c.bucket_id);
  GLint border = static_cast<GLint>(c.border);

  if (state_.bound_pixel_unpack_buffer.get()) {
    return error::kInvalidArguments;
  }
  Bucket* bucket = GetBucket(bucket_id);
  if (!bucket)
    return error::kInvalidArguments;
  uint32_t image_size = bucket->size();
  const void* data = bucket->GetData(0, image_size);
  DCHECK(data || !image_size);
  return DoCompressedTexImage(target, level, internal_format, width, height,
                              depth, border, image_size, data,
                              ContextState::k3D);
}
