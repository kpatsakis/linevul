void BlockLoop(base::WaitableEvent* completion, base::Callback<bool()> work) {
  do {
    completion->Wait();
  } while (work.Run());
  base::MessageLoop::current()->QuitNow();
}
