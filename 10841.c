TextureManager::TextureInfo* TextureManager::GetTextureInfo(
    GLuint client_id) {
  TextureInfoMap::iterator it = texture_infos_.find(client_id);
  return it != texture_infos_.end() ? it->second : NULL;
}
