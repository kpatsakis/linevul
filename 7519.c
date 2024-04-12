void GLES2DecoderImpl::DoGetVertexAttribImpl(
    GLuint index, GLenum pname, T* params) {
  VertexAttrib* attrib = state_.vertex_attrib_manager->GetVertexAttrib(index);
  if (!attrib) {
    LOCAL_SET_GL_ERROR(
        GL_INVALID_VALUE, "glGetVertexAttrib", "index out of range");
    return;
  }
  switch (pname) {
    case GL_CURRENT_VERTEX_ATTRIB:
      state_.attrib_values[index].GetValues(params);
      break;
    default: {
      GLint value = 0;
      GetVertexAttribHelper(attrib, pname, &value);
      *params = static_cast<T>(value);
      break;
    }
  }
}
