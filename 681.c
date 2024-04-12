void GLES2DecoderImpl::DoGetVertexAttribiv(GLuint index,
                                           GLenum pname,
                                           GLint* params,
                                           GLsizei params_size) {
  DoGetVertexAttribImpl<GLint>(index, pname, params);
}
