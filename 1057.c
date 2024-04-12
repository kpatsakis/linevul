void WebGLRenderingContextBase::hint(GLenum target, GLenum mode) {
  if (isContextLost())
    return;
  bool is_valid = false;
  switch (target) {
    case GL_GENERATE_MIPMAP_HINT:
      is_valid = true;
      break;
    case GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES:  // OES_standard_derivatives
      if (ExtensionEnabled(kOESStandardDerivativesName) || IsWebGL2OrHigher())
        is_valid = true;
      break;
  }
  if (!is_valid) {
    SynthesizeGLError(GL_INVALID_ENUM, "hint", "invalid target");
    return;
  }
  ContextGL()->Hint(target, mode);
 }
