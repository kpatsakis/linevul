void UserSelectionScreen::OnUserActivity(const ui::Event* event) {
  if (!password_clear_timer_.IsRunning()) {
    password_clear_timer_.Start(
        FROM_HERE, base::TimeDelta::FromSeconds(kPasswordClearTimeoutSec), this,
        &UserSelectionScreen::OnPasswordClearTimerExpired);
  }
  password_clear_timer_.Reset();
}
