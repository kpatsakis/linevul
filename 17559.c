bool TextureManager::TextureInfo::SetParameter(
    const FeatureInfo* feature_info, GLenum pname, GLint param) {
  DCHECK(feature_info);

  if (target_ == GL_TEXTURE_EXTERNAL_OES ||
      target_ == GL_TEXTURE_RECTANGLE_ARB) {
    if (pname == GL_TEXTURE_MIN_FILTER &&
        (param != GL_NEAREST && param != GL_LINEAR))
      return false;
    if ((pname == GL_TEXTURE_WRAP_S || pname == GL_TEXTURE_WRAP_T) &&
        param != GL_CLAMP_TO_EDGE)
      return false;
  }

  switch (pname) {
    case GL_TEXTURE_MIN_FILTER:
      if (!feature_info->validators()->texture_min_filter_mode.IsValid(param)) {
        return false;
      }
      min_filter_ = param;
      break;
    case GL_TEXTURE_MAG_FILTER:
      if (!feature_info->validators()->texture_mag_filter_mode.IsValid(param)) {
        return false;
      }
      mag_filter_ = param;
      break;
    case GL_TEXTURE_WRAP_S:
      if (!feature_info->validators()->texture_wrap_mode.IsValid(param)) {
        return false;
      }
      wrap_s_ = param;
      break;
    case GL_TEXTURE_WRAP_T:
      if (!feature_info->validators()->texture_wrap_mode.IsValid(param)) {
        return false;
      }
      wrap_t_ = param;
      break;
    case GL_TEXTURE_MAX_ANISOTROPY_EXT:
      break;
    case GL_TEXTURE_USAGE_ANGLE:
      if (!feature_info->validators()->texture_usage.IsValid(param)) {
        return false;
      }
      usage_ = param;
      break;
    default:
      NOTREACHED();
      return false;
  }
  Update(feature_info);
  UpdateCleared();
  return true;
}
