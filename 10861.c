PrintingContext::Result PrintingContext::OnError() {
  ResetSettings();
  return abort_printing_ ? CANCEL : FAILED;
}
