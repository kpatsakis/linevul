void WebGL2RenderingContextBase::uniform4ui(
    const WebGLUniformLocation* location,
    GLuint v0,
    GLuint v1,
    GLuint v2,
    GLuint v3) {
  if (isContextLost() || !location)
    return;

  if (location->Program() != current_program_) {
    SynthesizeGLError(GL_INVALID_OPERATION, "uniform4ui",
                      "location not for current program");
    return;
  }

  ContextGL()->Uniform4ui(location->Location(), v0, v1, v2, v3);
}
