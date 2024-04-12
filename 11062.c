void LockContentsView::OnPublicSessionLocalesChanged(
    const AccountId& account_id,
    const std::vector<mojom::LocaleItemPtr>& locales,
    const std::string& default_locale,
    bool show_advanced_view) {
  LoginUserView* user_view = TryToFindUserView(account_id);
  if (!user_view || !IsPublicAccountUser(user_view->current_user()))
    return;

  mojom::LoginUserInfoPtr user_info = user_view->current_user()->Clone();
  user_info->public_account_info->available_locales = mojo::Clone(locales);
  user_info->public_account_info->default_locale = default_locale;
  user_info->public_account_info->show_advanced_view = show_advanced_view;
  user_view->UpdateForUser(user_info, false /*animate*/);
}
