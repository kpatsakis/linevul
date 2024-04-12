  void OnSetIsInertOnUI(bool is_inert) {
    is_inert_ = is_inert;
    if (!msg_received_) {
      msg_received_ = true;
      message_loop_runner_->Quit();
    }
  }
