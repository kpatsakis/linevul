void PeopleHandler::OnUnifiedConsentToggleChanged(const base::ListValue* args) {
  bool is_toggle_checked = args->GetList()[0].GetBool();
  if (!is_toggle_checked) {
    unified_consent::metrics::RecordUnifiedConsentRevoked(
        unified_consent::metrics::UnifiedConsentRevokeReason::
            kUserDisabledSettingsToggle);
  }
}
