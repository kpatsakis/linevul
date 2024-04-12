ScriptValue WebGL2RenderingContextBase::getSamplerParameter(
    ScriptState* script_state,
    WebGLSampler* sampler,
    GLenum pname) {
  if (isContextLost() || !ValidateWebGLObject("getSamplerParameter", sampler))
    return ScriptValue::CreateNull(script_state);

  switch (pname) {
    case GL_TEXTURE_COMPARE_FUNC:
    case GL_TEXTURE_COMPARE_MODE:
    case GL_TEXTURE_MAG_FILTER:
    case GL_TEXTURE_MIN_FILTER:
    case GL_TEXTURE_WRAP_R:
    case GL_TEXTURE_WRAP_S:
    case GL_TEXTURE_WRAP_T: {
      GLint value = 0;
      ContextGL()->GetSamplerParameteriv(ObjectOrZero(sampler), pname, &value);
      return WebGLAny(script_state, static_cast<unsigned>(value));
    }
    case GL_TEXTURE_MAX_LOD:
    case GL_TEXTURE_MIN_LOD: {
      GLfloat value = 0.f;
      ContextGL()->GetSamplerParameterfv(ObjectOrZero(sampler), pname, &value);
      return WebGLAny(script_state, value);
    }
    default:
      SynthesizeGLError(GL_INVALID_ENUM, "getSamplerParameter",
                        "invalid parameter name");
      return ScriptValue::CreateNull(script_state);
  }
}
