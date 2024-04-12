error::Error GLES2DecoderPassthroughImpl::DoGetShaderiv(GLuint shader,
                                                        GLenum pname,
                                                        GLsizei bufsize,
                                                        GLsizei* length,
                                                        GLint* params) {
  api()->glGetShaderivRobustANGLEFn(GetShaderServiceID(shader, resources_),
                                    pname, bufsize, length, params);
  return error::kNoError;
}
