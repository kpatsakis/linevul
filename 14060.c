void GLES2DecoderImpl::DoGetVertexAttribfv(GLuint index,
                                           GLenum pname,
                                           GLfloat* params,
                                           GLsizei params_size) {
  DoGetVertexAttribImpl<GLfloat>(index, pname, params);
}
