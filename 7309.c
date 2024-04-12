bool PDFiumEngine::OnChar(const pp::KeyboardInputEvent& event) {
  if (last_page_mouse_down_ == -1)
    return false;

  base::string16 str = base::UTF8ToUTF16(event.GetCharacterText().AsString());
  return !!FORM_OnChar(form_, pages_[last_page_mouse_down_]->GetPage(), str[0],
                       event.GetModifiers());
}
