void AutofillManager::OnFormsSeen(const std::vector<FormData>& forms) {
  bool enabled = IsAutofillEnabled();
  if (!has_logged_autofill_enabled_) {
    metric_logger_->LogIsAutofillEnabledAtPageLoad(enabled);
    has_logged_autofill_enabled_ = true;
  }

  if (!enabled)
    return;

  ParseForms(forms);
}
