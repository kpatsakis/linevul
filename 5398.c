void WebGLRenderingContextBase::EnableOrDisable(GLenum capability,
                                                bool enable) {
  if (isContextLost())
    return;
  if (enable)
    ContextGL()->Enable(capability);
  else
    ContextGL()->Disable(capability);
}
