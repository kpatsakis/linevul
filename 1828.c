void OutOfProcessInstance::Alert(const std::string& message) {
  ModalDialog(this, "alert", message, std::string());
}
