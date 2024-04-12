void RendererSchedulerImpl::EndIdlePeriodForTesting(
    const base::Closure& callback,
    base::TimeTicks time_remaining) {
  main_thread_only().in_idle_period_for_testing = false;
  EndIdlePeriod();
  callback.Run();
}
