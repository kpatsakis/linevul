void Instance::Alert(const std::string& message) {
  GetWindowObject().Call("alert", message);
}
