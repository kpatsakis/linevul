void WebGL2RenderingContextBase::clearBufferuiv(GLenum buffer,
                                                GLint drawbuffer,
                                                const Vector<GLuint>& value,
                                                GLuint src_offset) {
  if (isContextLost() ||
      !ValidateClearBuffer("clearBufferuiv", buffer, value.size(), src_offset))
    return;

  ContextGL()->ClearBufferuiv(buffer, drawbuffer, value.data() + src_offset);
}
