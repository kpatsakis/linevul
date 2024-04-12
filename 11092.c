WebGLRenderingContextBase::getAttachedShaders(WebGLProgram* program) {
  if (isContextLost() || !ValidateWebGLObject("getAttachedShaders", program))
    return base::nullopt;

  HeapVector<Member<WebGLShader>> shader_objects;
  const GLenum kShaderType[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
  for (unsigned i = 0; i < sizeof(kShaderType) / sizeof(GLenum); ++i) {
    WebGLShader* shader = program->GetAttachedShader(kShaderType[i]);
    if (shader)
      shader_objects.push_back(shader);
  }
  return shader_objects;
}
