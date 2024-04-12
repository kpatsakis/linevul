RefPtr<WebTaskRunner> FrameFetchContext::GetLoadingTaskRunner() {
  if (IsDetached())
    return FetchContext::GetLoadingTaskRunner();
  return TaskRunnerHelper::Get(TaskType::kNetworking, GetFrame());
}
