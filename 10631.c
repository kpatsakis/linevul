SingleThreadTaskRunner* WebLocalFrameImpl::LoadingTaskRunner() {
  return GetFrame()
      ->FrameScheduler()
      ->LoadingTaskRunner()
      ->ToSingleThreadTaskRunner();
}
