  virtual void Run() {
    ui_controls::SendMouseEventsNotifyWhenDone(ui_controls::LEFT, state_,
                                               next_task_);
  }
