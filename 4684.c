void DevToolsWindow::ReadyForTest() {
  ready_for_test_ = true;
  if (!ready_for_test_callback_.is_null()) {
    ready_for_test_callback_.Run();
    ready_for_test_callback_ = base::Closure();
  }
}
