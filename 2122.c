void GLES2Implementation::MultiDrawArraysWEBGL(GLenum mode,
                                               const GLint* firsts,
                                               const GLsizei* counts,
                                               GLsizei drawcount) {
  GPU_CLIENT_SINGLE_THREAD_CHECK();
  GPU_CLIENT_LOG("[" << GetLogPrefix() << "] glMultiDrawArraysWEBGL("
                     << GLES2Util::GetStringDrawMode(mode) << ", " << firsts
                     << ", " << counts << ", " << drawcount << ")");
  if (drawcount < 0) {
    SetGLError(GL_INVALID_VALUE, "glMultiDrawArraysWEBGL", "drawcount < 0");
    return;
  }
  if (drawcount == 0) {
    return;
  }
  if (vertex_array_object_manager_->SupportsClientSideBuffers()) {
    SetGLError(GL_INVALID_OPERATION, "glMultiDrawArraysWEBGL",
               "Missing array buffer for vertex attribute");
    return;
  }
  MultiDrawArraysWEBGLHelper(mode, firsts, counts, drawcount);
  CheckGLError();
}
