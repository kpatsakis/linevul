void Browser::HandleKeyboardEvent(content::WebContents* source,
                                  const NativeWebKeyboardEvent& event) {
  window()->HandleKeyboardEvent(event);
}
