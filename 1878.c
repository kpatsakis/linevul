SingleThreadTaskRunner* WebLocalFrameImpl::UnthrottledTaskRunner() {
  return GetFrame()
      ->FrameScheduler()
      ->UnthrottledTaskRunner()
      ->ToSingleThreadTaskRunner();
}
