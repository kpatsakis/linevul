IdleTimeEstimator* RendererSchedulerImpl::GetIdleTimeEstimatorForTesting() {
  return &main_thread_only().idle_time_estimator;
}
