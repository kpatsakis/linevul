void GLES2DecoderImpl::DoBlitFramebufferCHROMIUM(
    GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1,
    GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1,
    GLbitfield mask, GLenum filter) {
  DCHECK(!ShouldDeferReads() && !ShouldDeferDraws());

  if (!CheckBoundFramebuffersValid("glBlitFramebufferCHROMIUM")) {
    return;
  }

  state_.SetDeviceCapabilityState(GL_SCISSOR_TEST, false);
  BlitFramebufferHelper(
      srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
  state_.SetDeviceCapabilityState(GL_SCISSOR_TEST,
                                  state_.enable_flags.scissor_test);
}
