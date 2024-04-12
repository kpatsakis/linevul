bool TextureManager::TextureInfo::MarkMipmapsGenerated(
    const FeatureInfo* feature_info) {
  if (!CanGenerateMipmaps(feature_info)) {
    return false;
  }
  for (size_t ii = 0; ii < level_infos_.size(); ++ii) {
    const TextureInfo::LevelInfo& info1 = level_infos_[ii][0];
    GLsizei width = info1.width;
    GLsizei height = info1.height;
    GLsizei depth = info1.depth;
    GLenum target = target_ == GL_TEXTURE_2D ? GL_TEXTURE_2D :
                               FaceIndexToGLTarget(ii);
    int num_mips = ComputeMipMapCount(width, height, depth);
    for (int level = 1; level < num_mips; ++level) {
      width = std::max(1, width >> 1);
      height = std::max(1, height >> 1);
      depth = std::max(1, depth >> 1);
      SetLevelInfo(feature_info,
                   target,
                   level,
                   info1.internal_format,
                   width,
                   height,
                   depth,
                   info1.border,
                   info1.format,
                   info1.type,
                   true);
    }
  }

  return true;
}
