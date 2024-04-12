ScriptedIdleTaskController& Document::EnsureScriptedIdleTaskController() {
  if (!scripted_idle_task_controller_) {
    scripted_idle_task_controller_ = ScriptedIdleTaskController::Create(this);
    if (!frame_ || !frame_->IsAttached() ||
        ExecutionContext::IsContextDestroyed()) {
      scripted_idle_task_controller_->ContextLifecycleStateChanged(
          mojom::FrameLifecycleState::kFrozen);
    }
  }
  return *scripted_idle_task_controller_;
}
