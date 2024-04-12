error::Error GLES2DecoderPassthroughImpl::DoIsTransformFeedback(
    GLuint transformfeedback,
    uint32_t* result) {
  *result = api()->glIsTransformFeedbackFn(GetTransformFeedbackServiceID(
      transformfeedback, &transform_feedback_id_map_));
  return error::kNoError;
}
