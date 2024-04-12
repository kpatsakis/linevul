bool WebGLRenderingContextBase::ValidateCopyTexFormat(const char* function_name,
                                                      GLenum internalformat) {
  if (!is_web_gl2_internal_formats_copy_tex_image_added_ &&
      IsWebGL2OrHigher()) {
    ADD_VALUES_TO_SET(supported_internal_formats_copy_tex_image_,
                      kSupportedInternalFormatsES3);
    is_web_gl2_internal_formats_copy_tex_image_added_ = true;
  }
  if (!is_ext_color_buffer_float_formats_added_ &&
      ExtensionEnabled(kEXTColorBufferFloatName)) {
    ADD_VALUES_TO_SET(supported_internal_formats_copy_tex_image_,
                      kSupportedInternalFormatsCopyTexImageFloatES3);
    is_ext_color_buffer_float_formats_added_ = true;
  }

  if (supported_internal_formats_copy_tex_image_.find(internalformat) ==
      supported_internal_formats_copy_tex_image_.end()) {
    SynthesizeGLError(GL_INVALID_ENUM, function_name, "invalid internalformat");
    return false;
  }

  return true;
}
