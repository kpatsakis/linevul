bool AutocompleteEditModel::CanPasteAndGo(const string16& text) const {
  if (!view_->GetCommandUpdater()->IsCommandEnabled(IDC_OPEN_CURRENT_URL))
    return false;

  profile_->GetAutocompleteClassifier()->Classify(text, string16(),
      false, false, &paste_and_go_match_, &paste_and_go_alternate_nav_url_);
  return paste_and_go_match_.destination_url.is_valid();
}
