bool ExtensionInstallUI::Prompt::HasAbortButtonLabel() const {
  return kAbortButtonIds[type_] > 0;
}
