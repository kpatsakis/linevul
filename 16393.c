WebGLTexture* WebGL2RenderingContextBase::ValidateTexture3DBinding(
    const char* function_name,
    GLenum target) {
  WebGLTexture* tex = nullptr;
  switch (target) {
    case GL_TEXTURE_2D_ARRAY:
      tex = texture_units_[active_texture_unit_].texture2d_array_binding_.Get();
      break;
    case GL_TEXTURE_3D:
      tex = texture_units_[active_texture_unit_].texture3d_binding_.Get();
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
