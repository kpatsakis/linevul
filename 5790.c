void LoginDisplayHostWebUI::OnPreferencesChanged() {
  if (is_showing_login_)
    login_display_->OnPreferencesChanged();
}
