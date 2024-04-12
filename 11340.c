void LockContentsView::UpdateAuthForAuthUser(LoginAuthUserView* opt_to_update,
                                             LoginAuthUserView* opt_to_hide,
                                             bool animate) {
  if (animate) {
    if (opt_to_update)
      opt_to_update->CaptureStateForAnimationPreLayout();
    if (opt_to_hide)
      opt_to_hide->CaptureStateForAnimationPreLayout();
  }

  if (opt_to_update) {
    UserState* state = FindStateForUser(
        opt_to_update->current_user()->basic_user_info->account_id);
    uint32_t to_update_auth;
    if (state->force_online_sign_in) {
      to_update_auth = LoginAuthUserView::AUTH_ONLINE_SIGN_IN;
    } else if (state->disable_auth) {
      to_update_auth = LoginAuthUserView::AUTH_DISABLED;
    } else {
      to_update_auth = LoginAuthUserView::AUTH_PASSWORD;
      keyboard::KeyboardController* keyboard_controller =
          GetKeyboardController();
      const bool keyboard_visible =
          keyboard_controller ? keyboard_controller->keyboard_visible() : false;
      if (state->show_pin && !keyboard_visible &&
          state->fingerprint_state ==
              mojom::FingerprintUnlockState::UNAVAILABLE) {
        to_update_auth |= LoginAuthUserView::AUTH_PIN;
      }
      if (state->enable_tap_auth)
        to_update_auth |= LoginAuthUserView::AUTH_TAP;
      if (state->fingerprint_state !=
          mojom::FingerprintUnlockState::UNAVAILABLE) {
        to_update_auth |= LoginAuthUserView::AUTH_FINGERPRINT;
      }
    }
    opt_to_update->SetAuthMethods(to_update_auth);
  }
  if (opt_to_hide)
    opt_to_hide->SetAuthMethods(LoginAuthUserView::AUTH_NONE);

  Layout();

  if (animate) {
    if (opt_to_update)
      opt_to_update->ApplyAnimationPostLayout();
    if (opt_to_hide)
      opt_to_hide->ApplyAnimationPostLayout();
  }
}
