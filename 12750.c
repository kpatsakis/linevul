void PasswordAutofillAgent::PasswordValueGatekeeper::Reset() {
  was_user_gesture_seen_ = false;
  elements_.clear();
}
