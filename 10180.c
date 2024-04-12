bool WebGLRenderingContextBase::ValidateWebGLProgramOrShader(
    const char* function_name,
    WebGLObject* object) {
  if (isContextLost())
    return false;
  DCHECK(object);
  if (!object->HasObject()) {
    SynthesizeGLError(GL_INVALID_VALUE, function_name,
                      "attempt to use a deleted object");
    return false;
  }
  if (!object->Validate(ContextGroup(), this)) {
    SynthesizeGLError(GL_INVALID_OPERATION, function_name,
                      "object does not belong to this context");
    return false;
  }
  return true;
}
