void AutofillExternalDelegate::OnAutofillAvailabilityEvent(
    bool has_suggestions) {
  if (has_suggestions) {
    ui::AXPlatformNode::OnInputSuggestionsAvailable();
  } else {
    ui::AXPlatformNode::OnInputSuggestionsUnavailable();
  }
}
