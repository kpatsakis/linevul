void LockContentsView::RemoveUser(bool is_primary) {
  if (Shell::Get()->login_screen_controller()->IsAuthenticating())
    return;

  LoginBigUserView* to_remove =
      is_primary ? primary_big_view_ : opt_secondary_big_view_;
  DCHECK(to_remove->GetCurrentUser()->can_remove);
  AccountId user = to_remove->GetCurrentUser()->basic_user_info->account_id;

  Shell::Get()->login_screen_controller()->RemoveUser(user);

  std::vector<mojom::LoginUserInfoPtr> new_users;
  if (!is_primary)
    new_users.push_back(primary_big_view_->GetCurrentUser()->Clone());
  if (is_primary && opt_secondary_big_view_)
    new_users.push_back(opt_secondary_big_view_->GetCurrentUser()->Clone());
  if (users_list_) {
    for (int i = 0; i < users_list_->user_count(); ++i) {
      new_users.push_back(
          users_list_->user_view_at(i)->current_user()->Clone());
    }
  }
  data_dispatcher_->NotifyUsers(new_users);
}
