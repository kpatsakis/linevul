void WebGL2RenderingContextBase::resumeTransformFeedback() {
  if (isContextLost())
    return;

  if (transform_feedback_binding_ &&
      transform_feedback_binding_->GetProgram() != current_program_) {
    SynthesizeGLError(GL_INVALID_OPERATION, "resumeTransformFeedback",
                      "the program object is not active");
    return;
  }

  ContextGL()->ResumeTransformFeedback();
}
