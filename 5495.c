WebGLTexture* WebGLRenderingContextBase::ValidateTextureBinding(
    const char* function_name,
    GLenum target) {
  WebGLTexture* tex = nullptr;
  switch (target) {
    case GL_TEXTURE_2D:
      tex = texture_units_[active_texture_unit_].texture2d_binding_.Get();
      break;
    case GL_TEXTURE_CUBE_MAP:
      tex =
          texture_units_[active_texture_unit_].texture_cube_map_binding_.Get();
      break;
    case GL_TEXTURE_3D:
      if (!IsWebGL2OrHigher()) {
        SynthesizeGLError(GL_INVALID_ENUM, function_name,
                          "invalid texture target");
        return nullptr;
      }
      tex = texture_units_[active_texture_unit_].texture3d_binding_.Get();
      break;
    case GL_TEXTURE_2D_ARRAY:
      if (!IsWebGL2OrHigher()) {
        SynthesizeGLError(GL_INVALID_ENUM, function_name,
                          "invalid texture target");
        return nullptr;
      }
      tex = texture_units_[active_texture_unit_].texture2d_array_binding_.Get();
      break;
    case GL_TEXTURE_VIDEO_IMAGE_WEBGL:
      if (!ExtensionEnabled(kWebGLVideoTextureName)) {
        SynthesizeGLError(GL_INVALID_ENUM, function_name,
                          "invalid texture target");
        return nullptr;
      }
      tex = texture_units_[active_texture_unit_]
                .texture_video_image_binding_.Get();
      break;
    default:
      SynthesizeGLError(GL_INVALID_ENUM, function_name,
                        "invalid texture target");
      return nullptr;
  }
  if (!tex)
    SynthesizeGLError(GL_INVALID_OPERATION, function_name,
                      "no texture bound to target");
  return tex;
}
