const char* RendererSchedulerImpl::UseCaseToString(UseCase use_case) {
  switch (use_case) {
    case UseCase::kNone:
      return "none";
    case UseCase::kCompositorGesture:
      return "compositor_gesture";
    case UseCase::kMainThreadCustomInputHandling:
      return "main_thread_custom_input_handling";
    case UseCase::kSynchronizedGesture:
      return "synchronized_gesture";
    case UseCase::kTouchstart:
      return "touchstart";
    case UseCase::kLoading:
      return "loading";
    case UseCase::kMainThreadGesture:
      return "main_thread_gesture";
    default:
      NOTREACHED();
      return nullptr;
  }
}
