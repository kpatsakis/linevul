void GLES2DecoderImpl::DoBeginTransformFeedback(GLenum primitive_mode) {
  const char* function_name = "glBeginTransformFeedback";
  TransformFeedback* transform_feedback = state_.bound_transform_feedback.get();
  DCHECK(transform_feedback);
  if (transform_feedback->active()) {
    LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, function_name,
                       "transform feedback is already active");
    return;
  }
  if (!CheckCurrentProgram(function_name)) {
    return;
  }
  Program* program = state_.current_program.get();
  DCHECK(program);
  size_t required_buffer_count =
      program->effective_transform_feedback_varyings().size();
  if (required_buffer_count == 0) {
    LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, function_name,
                       "no active transform feedback varyings");
    return;
  }
  if (required_buffer_count > 1 &&
      GL_INTERLEAVED_ATTRIBS ==
          program->effective_transform_feedback_buffer_mode()) {
    required_buffer_count = 1;
  }
  for (size_t ii = 0; ii < required_buffer_count; ++ii) {
    Buffer* buffer = transform_feedback->GetBufferBinding(ii);
    if (!buffer) {
      std::string msg = base::StringPrintf("missing buffer bound at index %i",
                                           static_cast<int>(ii));
      LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, function_name, msg.c_str());
      return;
    }
    if (buffer->GetMappedRange()) {
      std::string msg = base::StringPrintf(
          "bound buffer bound at index %i is mapped", static_cast<int>(ii));
      LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, function_name, msg.c_str());
      return;
    }
    if (buffer->IsDoubleBoundForTransformFeedback()) {
      std::string msg = base::StringPrintf(
          "buffer at index %i is bound for multiple transform feedback outputs",
          static_cast<int>(ii));
      LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, function_name, msg.c_str());
      return;
    }
  }
  transform_feedback->DoBeginTransformFeedback(primitive_mode);
  DCHECK(transform_feedback->active());
}
