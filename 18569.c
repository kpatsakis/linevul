void PDFiumEngine::KillFormFocus() {
  FORM_ForceToKillFocus(form_);
  SetInFormTextArea(false);
}
