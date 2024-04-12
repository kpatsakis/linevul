bool GLES2DecoderImpl::DoIsRenderbuffer(GLuint client_id) {
  const RenderbufferManager::RenderbufferInfo* info =
      GetRenderbufferInfo(client_id);
  return info && info->IsValid();
}
