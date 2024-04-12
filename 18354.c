Vector<GLuint> WebGL2RenderingContextBase::getUniformIndices(
    WebGLProgram* program,
    const Vector<String>& uniform_names) {
  Vector<GLuint> result;
  if (isContextLost() || !ValidateWebGLObject("getUniformIndices", program))
    return result;

  Vector<CString> keep_alive;  // Must keep these instances alive while looking
  Vector<const char*> uniform_strings;
  for (size_t i = 0; i < uniform_names.size(); ++i) {
    keep_alive.push_back(uniform_names[i].Ascii());
    uniform_strings.push_back(keep_alive.back().data());
  }

  result.resize(uniform_names.size());
  ContextGL()->GetUniformIndices(ObjectOrZero(program), uniform_strings.size(),
                                 uniform_strings.data(), result.data());
  return result;
}
