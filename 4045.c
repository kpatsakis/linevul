bool TextureManager::ValidForTarget(
    GLenum target, GLint level, GLsizei width, GLsizei height, GLsizei depth) {
  GLsizei max_size = MaxSizeForTarget(target);
  return level >= 0 &&
         width >= 0 &&
         height >= 0 &&
         depth >= 0 &&
         level < MaxLevelsForTarget(target) &&
         width <= max_size &&
         height <= max_size &&
         depth <= max_size &&
         (level == 0 || feature_info_->feature_flags().npot_ok ||
          (!GLES2Util::IsNPOT(width) &&
           !GLES2Util::IsNPOT(height) &&
           !GLES2Util::IsNPOT(depth))) &&
         (target != GL_TEXTURE_CUBE_MAP || (width == height && depth == 1)) &&
         (target != GL_TEXTURE_2D || (depth == 1));
}
