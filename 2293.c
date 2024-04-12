void GLES2Implementation::DrawElements(GLenum mode,
                                       GLsizei count,
                                       GLenum type,
                                       const void* indices) {
  GPU_CLIENT_SINGLE_THREAD_CHECK();
  GPU_CLIENT_LOG("[" << GetLogPrefix() << "] glDrawElements("
                     << GLES2Util::GetStringDrawMode(mode) << ", " << count
                     << ", " << GLES2Util::GetStringIndexType(type) << ", "
                     << static_cast<const void*>(indices) << ")");
  DrawElementsImpl(mode, count, type, indices, "glDrawElements");
}
