void BlinkTestRunner::SetEditCommand(const std::string& name,
                                     const std::string& value) {
  render_view()->SetEditCommandForNextKeyEvent(name, value);
}
