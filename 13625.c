void ChromePasswordManagerClient::OnInputEvent(
    const blink::WebInputEvent& event) {
  if (event.GetType() != blink::WebInputEvent::kChar)
    return;
  const blink::WebKeyboardEvent& key_event =
      static_cast<const blink::WebKeyboardEvent&>(event);
  password_reuse_detection_manager_.OnKeyPressed(key_event.text);
}
