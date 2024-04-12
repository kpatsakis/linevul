SelectFileDialog* SelectFileDialog::Create(Listener* listener) {
  return new SelectFileDialogImpl(listener);
}
