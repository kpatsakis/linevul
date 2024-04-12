void LockContentsView::UpdateEasyUnlockIconForUser(const AccountId& user) {
  LoginBigUserView* big_view =
      TryToFindBigUser(user, false /*require_auth_active*/);
  if (!big_view || !big_view->auth_user())
    return;

  UserState* state = FindStateForUser(user);
  DCHECK(state);

  if (!state->easy_unlock_state) {
    big_view->auth_user()->SetEasyUnlockIcon(mojom::EasyUnlockIconId::NONE,
                                             base::string16());
    return;
  }

  base::string16 accessibility_label = state->easy_unlock_state->aria_label;
  if (accessibility_label.empty())
    accessibility_label = state->easy_unlock_state->tooltip;

  big_view->auth_user()->SetEasyUnlockIcon(state->easy_unlock_state->icon,
                                           accessibility_label);
}
