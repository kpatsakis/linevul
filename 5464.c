bool PDFiumEngine::OnKeyDown(const pp::KeyboardInputEvent& event) {
  if (last_page_mouse_down_ == -1)
    return false;

  bool rv = !!FORM_OnKeyDown(form_, pages_[last_page_mouse_down_]->GetPage(),
                             event.GetKeyCode(), event.GetModifiers());

  if (event.GetKeyCode() == ui::VKEY_BACK ||
      event.GetKeyCode() == ui::VKEY_ESCAPE) {
    std::string str;
    str.push_back(event.GetKeyCode());
    pp::KeyboardInputEvent synthesized(pp::KeyboardInputEvent(
        client_->GetPluginInstance(), PP_INPUTEVENT_TYPE_CHAR,
        event.GetTimeStamp(), event.GetModifiers(), event.GetKeyCode(), str));
    OnChar(synthesized);
  }

  return rv;
}
