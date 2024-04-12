void AutomationProvider::OverrideEncoding(int tab_handle,
                                          const std::string& encoding_name,
                                          bool* success) {
  *success = false;
  if (tab_tracker_->ContainsHandle(tab_handle)) {
    NavigationController* nav = tab_tracker_->GetResource(tab_handle);
    if (!nav)
      return;
    Browser* browser = FindAndActivateTab(nav);

    if (browser &&
        browser->command_updater()->IsCommandEnabled(IDC_ENCODING_MENU)) {
      int selected_encoding_id =
          CharacterEncoding::GetCommandIdByCanonicalEncodingName(encoding_name);
      if (selected_encoding_id) {
        browser->OverrideEncoding(selected_encoding_id);
        *success = true;
      }
    } else {
      TabContents* contents = nav->tab_contents();
      if (!contents)
        return;
      const std::string selected_encoding =
          CharacterEncoding::GetCanonicalEncodingNameByAliasName(encoding_name);
      if (selected_encoding.empty())
        return;
      contents->SetOverrideEncoding(selected_encoding);
    }
  }
}
