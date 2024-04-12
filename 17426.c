void GLES2Implementation::DisableVertexAttribArray(GLuint index) {
  GPU_CLIENT_SINGLE_THREAD_CHECK();
  GPU_CLIENT_LOG("[" << GetLogPrefix() << "] glDisableVertexAttribArray("
                     << index << ")");
  vertex_array_object_manager_->SetAttribEnable(index, false);
  helper_->DisableVertexAttribArray(index);
  CheckGLError();
}
