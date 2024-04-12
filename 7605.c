  void DrainMessageLoops() {
    MessageLoop::current()->RunUntilIdle();
    message_loop_.RunUntilIdle();
  }
