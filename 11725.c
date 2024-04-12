void PasswordAutofillAgent::PasswordValueGatekeeper::OnUserGesture() {
  if (was_user_gesture_seen_)
    return;

  was_user_gesture_seen_ = true;

  for (WebInputElement& element : elements_)
    ShowValue(&element);

  elements_.clear();
}
