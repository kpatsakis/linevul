void WebGLRenderingContextBase::blendFunc(GLenum sfactor, GLenum dfactor) {
  if (isContextLost() ||
      !ValidateBlendFuncFactors("blendFunc", sfactor, dfactor))
    return;
  ContextGL()->BlendFunc(sfactor, dfactor);
}
