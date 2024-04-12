void GLES2DecoderImpl::DoClear(GLbitfield mask) {
  if (CheckFramebufferComplete("glClear")) {
    ApplyDirtyState();
    glClear(mask);
  }
}
