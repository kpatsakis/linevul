const char* WebGL2RenderingContextBase::ValidateGetBufferSubData(
    const char* function_name,
    GLenum target,
    GLintptr source_byte_offset,
    DOMArrayBufferView* destination_array_buffer_view,
    GLuint destination_offset,
    GLuint length,
    WebGLBuffer** out_source_buffer,
    void** out_destination_data_ptr,
    long long* out_destination_byte_length) {
  if (isContextLost()) {
    return "Context lost";
  }

  if (!ValidateValueFitNonNegInt32(function_name, "srcByteOffset",
                                   source_byte_offset)) {
    return "Invalid value: srcByteOffset";
  }

  WebGLBuffer* source_buffer = ValidateBufferDataTarget(function_name, target);
  if (!source_buffer) {
    return "Invalid operation: no buffer bound to target";
  }
  if (transform_feedback_binding_->active() &&
      transform_feedback_binding_->UsesBuffer(source_buffer)) {
    SynthesizeGLError(GL_INVALID_OPERATION, function_name,
                      "buffer in use for transform feedback");
    return "Invalid operation: buffer in use for transform feedback";
  }
  *out_source_buffer = source_buffer;

  if (!ValidateSubSourceAndGetData(
          destination_array_buffer_view, destination_offset, length,
          out_destination_data_ptr, out_destination_byte_length)) {
    SynthesizeGLError(GL_INVALID_VALUE, function_name, "overflow of dstData");
    return "Invalid value: overflow of dstData";
  }

  return nullptr;
}
