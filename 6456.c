  void WakeUp() {
    if (loop_)
      loop_->Quit();
  }
