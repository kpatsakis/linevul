  virtual void TearDown() {
    ui_loop_.RunAllPending();
    io_thread_.Stop();
    ui_loop_.RunAllPending();
  }
