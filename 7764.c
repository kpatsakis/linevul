void GLES2DecoderImpl::DoPauseTransformFeedback() {
  DCHECK(state_.bound_transform_feedback.get());
  if (!state_.bound_transform_feedback->active() ||
      state_.bound_transform_feedback->paused()) {
    LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, "glPauseTransformFeedback",
                       "transform feedback is not active or already paused");
    return;
  }
  state_.bound_transform_feedback->DoPauseTransformFeedback();
}
