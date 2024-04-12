bool PrintViewManagerBase::RenderAllMissingPagesNow() {
  if (!print_job_.get() || !print_job_->is_job_pending())
    return false;

  if (!web_contents() ||
      !web_contents()->GetRenderViewHost() ||
      !web_contents()->GetRenderViewHost()->IsRenderViewLive()) {
    return false;
  }

  if (print_job_->document() && print_job_->document()->IsComplete()) {
    printing_succeeded_ = true;
    return true;
  }

  if (!RunInnerMessageLoop()) {
    return false;
  }
  return true;
}
