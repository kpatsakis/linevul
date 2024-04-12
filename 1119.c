bool WebGLRenderingContextBase::ValidateTexFuncFormatAndType(
    const char* function_name,
    TexImageFunctionType function_type,
    GLenum internalformat,
    GLenum format,
    GLenum type,
    GLint level) {
  if (!is_web_gl2_formats_types_added_ && IsWebGL2OrHigher()) {
    ADD_VALUES_TO_SET(supported_internal_formats_,
                      kSupportedInternalFormatsES3);
    ADD_VALUES_TO_SET(supported_internal_formats_,
                      kSupportedInternalFormatsTexImageES3);
    ADD_VALUES_TO_SET(supported_formats_, kSupportedFormatsES3);
    ADD_VALUES_TO_SET(supported_types_, kSupportedTypesES3);
    is_web_gl2_formats_types_added_ = true;
  }

  if (!IsWebGL2OrHigher()) {
    AddExtensionSupportedFormatsTypes();
  }

  if (internalformat != 0 && supported_internal_formats_.find(internalformat) ==
                                 supported_internal_formats_.end()) {
    if (function_type == kTexImage) {
      SynthesizeGLError(GL_INVALID_VALUE, function_name,
                        "invalid internalformat");
    } else {
      SynthesizeGLError(GL_INVALID_ENUM, function_name,
                        "invalid internalformat");
    }
    return false;
  }
  if (supported_formats_.find(format) == supported_formats_.end()) {
    SynthesizeGLError(GL_INVALID_ENUM, function_name, "invalid format");
    return false;
  }
  if (supported_types_.find(type) == supported_types_.end()) {
    SynthesizeGLError(GL_INVALID_ENUM, function_name, "invalid type");
    return false;
  }

  if (format == GL_DEPTH_COMPONENT && level > 0 && !IsWebGL2OrHigher()) {
    SynthesizeGLError(GL_INVALID_OPERATION, function_name,
                      "level must be 0 for DEPTH_COMPONENT format");
    return false;
  }
  if (format == GL_DEPTH_STENCIL_OES && level > 0 && !IsWebGL2OrHigher()) {
    SynthesizeGLError(GL_INVALID_OPERATION, function_name,
                      "level must be 0 for DEPTH_STENCIL format");
    return false;
  }

  return true;
}
