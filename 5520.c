bool WebGLRenderingContextBase::ValidateShaderType(const char* function_name,
                                                   GLenum shader_type) {
  switch (shader_type) {
    case GL_VERTEX_SHADER:
    case GL_FRAGMENT_SHADER:
      return true;
    case GL_COMPUTE_SHADER:
      if (context_type_ != Platform::kWebGL2ComputeContextType) {
        SynthesizeGLError(GL_INVALID_ENUM, function_name,
                          "invalid shader type");
        return false;
      }
      return true;
    default:
      SynthesizeGLError(GL_INVALID_ENUM, function_name, "invalid shader type");
      return false;
  }
}
