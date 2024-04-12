void EglRenderingVDAClient::DismissPictureBuffer(int32 picture_buffer_id) {
  PictureBufferById::iterator it =
      picture_buffers_by_id_.find(picture_buffer_id);
  CHECK(it != picture_buffers_by_id_.end());
  CHECK_EQ(outstanding_texture_ids_.erase(it->second->texture_id()), 1U);
  rendering_helper_->DeleteTexture(it->second->texture_id());
  delete it->second;
  picture_buffers_by_id_.erase(it);
}
