void AutofillManager::UploadFormDataAsyncCallback(
    const FormStructure* submitted_form,
    const TimeTicks& load_time,
    const TimeTicks& interaction_time,
    const TimeTicks& submission_time,
    bool observed_submission) {
  if (submitted_form->ShouldRunHeuristics() ||
      submitted_form->ShouldBeQueried()) {
    submitted_form->LogQualityMetrics(
        load_time, interaction_time, submission_time,
        form_interactions_ukm_logger_.get(), did_show_suggestions_,
        observed_submission);
  }
  if (submitted_form->ShouldBeUploaded())
    UploadFormData(*submitted_form, observed_submission);
}
