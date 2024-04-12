Response TargetHandler::SetAttachToFrames(bool value) {
  auto_attacher_.SetAttachToFrames(value);
  if (!auto_attacher_.ShouldThrottleFramesNavigation())
    ClearThrottles();
  return Response::OK();
}
