  void QuitIOLoop() {
    fake_io_thread_completion_.Signal();
    content::RunMessageLoop();
  }
