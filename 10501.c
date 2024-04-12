void GLES2Implementation::CompressedTexImage2D(GLenum target,
                                               GLint level,
                                               GLenum internalformat,
                                               GLsizei width,
                                               GLsizei height,
                                               GLint border,
                                               GLsizei image_size,
                                               const void* data) {
  GPU_CLIENT_SINGLE_THREAD_CHECK();
  GPU_CLIENT_LOG(
      "[" << GetLogPrefix() << "] glCompressedTexImage2D("
          << GLES2Util::GetStringTextureTarget(target) << ", " << level << ", "
          << GLES2Util::GetStringCompressedTextureFormat(internalformat) << ", "
          << width << ", " << height << ", " << border << ", " << image_size
          << ", " << static_cast<const void*>(data) << ")");
  if (width < 0 || height < 0 || level < 0) {
    SetGLError(GL_INVALID_VALUE, "glCompressedTexImage2D", "dimension < 0");
    return;
  }
  if (border != 0) {
    SetGLError(GL_INVALID_VALUE, "glCompressedTexImage2D", "border != 0");
    return;
  }
  if (bound_pixel_unpack_transfer_buffer_id_) {
    GLuint offset = ToGLuint(data);
    BufferTracker::Buffer* buffer = GetBoundPixelTransferBufferIfValid(
        bound_pixel_unpack_transfer_buffer_id_, "glCompressedTexImage2D",
        offset, image_size);
    if (buffer && buffer->shm_id() != -1) {
      helper_->CompressedTexImage2D(target, level, internalformat, width,
                                    height, image_size, buffer->shm_id(),
                                    buffer->shm_offset() + offset);
      buffer->set_last_usage_token(helper_->InsertToken());
    }
    return;
  }
  if (bound_pixel_unpack_buffer_) {
    helper_->CompressedTexImage2D(target, level, internalformat, width, height,
                                  image_size, 0, ToGLuint(data));
  } else if (data) {
    SetBucketContents(kResultBucketId, data, image_size);
    helper_->CompressedTexImage2DBucket(target, level, internalformat, width,
                                        height, kResultBucketId);
    helper_->SetBucketSize(kResultBucketId, 0);
  } else {
    helper_->CompressedTexImage2D(target, level, internalformat, width, height,
                                  image_size, 0, 0);
  }
  CheckGLError();
}
