void LockContentsView::SwapToBigUser(int user_index) {
  if (Shell::Get()->login_screen_controller()->IsAuthenticating())
    return;

  DCHECK(users_list_);
  LoginUserView* view = users_list_->user_view_at(user_index);
  DCHECK(view);
  mojom::LoginUserInfoPtr previous_big_user =
      primary_big_view_->GetCurrentUser()->Clone();
  mojom::LoginUserInfoPtr new_big_user = view->current_user()->Clone();

  view->UpdateForUser(previous_big_user, true /*animate*/);
  primary_big_view_->UpdateForUser(new_big_user);
  LayoutAuth(primary_big_view_, nullptr, true /*animate*/);
  OnBigUserChanged();
}
