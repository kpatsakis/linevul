  bool WaitForFinish() {
    if (!finished_) {
      waiting_ = true;
      ui_test_utils::RunMessageLoop();
      waiting_ = false;
    }
    return finished_;
  }
