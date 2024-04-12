ScriptValue WebGLRenderingContextBase::getShaderParameter(
    ScriptState* script_state,
    WebGLShader* shader,
    GLenum pname) {
  if (!ValidateWebGLProgramOrShader("getShaderParameter", shader)) {
    return ScriptValue::CreateNull(script_state);
  }
  GLint value = 0;
  switch (pname) {
    case GL_DELETE_STATUS:
      return WebGLAny(script_state, shader->MarkedForDeletion());
    case GL_COMPILE_STATUS:
      ContextGL()->GetShaderiv(ObjectOrZero(shader), pname, &value);
      return WebGLAny(script_state, static_cast<bool>(value));
    case GL_COMPLETION_STATUS_KHR:
      if (!ExtensionEnabled(kKHRParallelShaderCompileName)) {
        SynthesizeGLError(GL_INVALID_ENUM, "getShaderParameter",
                          "invalid parameter name");
        return ScriptValue::CreateNull(script_state);
      }
      ContextGL()->GetShaderiv(ObjectOrZero(shader), pname, &value);
      return WebGLAny(script_state, static_cast<bool>(value));
    case GL_SHADER_TYPE:
      ContextGL()->GetShaderiv(ObjectOrZero(shader), pname, &value);
      return WebGLAny(script_state, static_cast<unsigned>(value));
    default:
      SynthesizeGLError(GL_INVALID_ENUM, "getShaderParameter",
                        "invalid parameter name");
      return ScriptValue::CreateNull(script_state);
  }
}
