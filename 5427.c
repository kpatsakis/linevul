void GLES2Implementation::DeleteFramebuffersHelper(GLsizei n,
                                                   const GLuint* framebuffers) {
  helper_->DeleteFramebuffersImmediate(n, framebuffers);
  IdAllocator* id_allocator = GetIdAllocator(IdNamespaces::kFramebuffers);
  for (GLsizei ii = 0; ii < n; ++ii) {
    id_allocator->FreeID(framebuffers[ii]);
    if (framebuffers[ii] == bound_framebuffer_) {
      bound_framebuffer_ = 0;
    }
    if (framebuffers[ii] == bound_read_framebuffer_) {
      bound_read_framebuffer_ = 0;
    }
  }
}
