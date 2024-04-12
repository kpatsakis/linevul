bool WebGL2RenderingContextBase::ValidateBufferTargetCompatibility(
    const char* function_name,
    GLenum target,
    WebGLBuffer* buffer) {
  DCHECK(buffer);

  switch (buffer->GetInitialTarget()) {
    case GL_ELEMENT_ARRAY_BUFFER:
      switch (target) {
        case GL_ARRAY_BUFFER:
        case GL_PIXEL_PACK_BUFFER:
        case GL_PIXEL_UNPACK_BUFFER:
        case GL_TRANSFORM_FEEDBACK_BUFFER:
        case GL_UNIFORM_BUFFER:
          SynthesizeGLError(
              GL_INVALID_OPERATION, function_name,
              "element array buffers can not be bound to a different target");

          return false;
        default:
          break;
      }
      break;
    case GL_ARRAY_BUFFER:
    case GL_COPY_READ_BUFFER:
    case GL_COPY_WRITE_BUFFER:
    case GL_PIXEL_PACK_BUFFER:
    case GL_PIXEL_UNPACK_BUFFER:
    case GL_UNIFORM_BUFFER:
    case GL_TRANSFORM_FEEDBACK_BUFFER:
      if (target == GL_ELEMENT_ARRAY_BUFFER) {
        SynthesizeGLError(GL_INVALID_OPERATION, function_name,
                          "buffers bound to non ELEMENT_ARRAY_BUFFER targets "
                          "can not be bound to ELEMENT_ARRAY_BUFFER target");
        return false;
      }
      break;
    default:
      break;
  }

  if (target == GL_TRANSFORM_FEEDBACK_BUFFER) {
    if (IsBufferBoundToNonTransformFeedback(buffer)) {
      SynthesizeGLError(GL_INVALID_OPERATION, function_name,
                        "a buffer bound to TRANSFORM_FEEDBACK_BUFFER can not "
                        "be bound to any other targets");
      return false;
    }
  } else if (IsBufferBoundToTransformFeedback(buffer)) {
    SynthesizeGLError(GL_INVALID_OPERATION, function_name,
                      "a buffer bound to TRANSFORM_FEEDBACK_BUFFER can not be "
                      "bound to any other targets");
    return false;
  }

  return true;
}
