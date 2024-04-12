void WebSocketExperimentRunner::Stop() {
  if (runner.get())
    runner->Cancel();
  runner = NULL;
}
