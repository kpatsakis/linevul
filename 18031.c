  void WaitForSelectedText(const std::string& expected_text) {
    if (last_selected_text_ == expected_text)
      return;
    expected_text_ = expected_text;
    loop_runner_ = new MessageLoopRunner();
    loop_runner_->Run();
  }
