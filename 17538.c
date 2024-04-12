uint32 GLES2DecoderImpl::GetTextureUploadCount() {
  return texture_state_.texture_upload_count +
         async_pixel_transfer_manager_->GetTextureUploadCount();
}
