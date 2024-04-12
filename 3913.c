WebSocketExperimentRunner::WebSocketExperimentRunner()
    : next_state_(STATE_NONE),
      task_state_(STATE_NONE),
      ALLOW_THIS_IN_INITIALIZER_LIST(
          task_callback_(this, &WebSocketExperimentRunner::OnTaskCompleted)) {
  WebSocketExperimentTask::InitHistogram();
  InitConfig();
}
