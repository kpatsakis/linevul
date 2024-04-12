ScriptValue WebGLRenderingContextBase::GetBooleanArrayParameter(
    ScriptState* script_state,
    GLenum pname) {
  if (pname != GL_COLOR_WRITEMASK) {
    NOTIMPLEMENTED();
    return WebGLAny(script_state, nullptr, 0);
  }
  GLboolean value[4] = {0};
  if (!isContextLost())
    ContextGL()->GetBooleanv(pname, value);
  bool bool_value[4];
  for (int ii = 0; ii < 4; ++ii)
    bool_value[ii] = static_cast<bool>(value[ii]);
  return WebGLAny(script_state, bool_value, 4);
}
