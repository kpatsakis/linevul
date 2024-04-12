void WebGLRenderingContextBase::blendEquationSeparate(GLenum mode_rgb,
                                                      GLenum mode_alpha) {
  if (isContextLost() ||
      !ValidateBlendEquation("blendEquationSeparate", mode_rgb) ||
      !ValidateBlendEquation("blendEquationSeparate", mode_alpha))
    return;
  ContextGL()->BlendEquationSeparate(mode_rgb, mode_alpha);
}
