void Document::SendSensitiveInputVisibility() {
  if (sensitive_input_visibility_task_.IsActive())
    return;

  sensitive_input_visibility_task_ =
      TaskRunnerHelper::Get(TaskType::kUnspecedLoading, this)
          ->PostCancellableTask(
              BLINK_FROM_HERE,
              WTF::Bind(&Document::SendSensitiveInputVisibilityInternal,
                        WrapWeakPersistent(this)));
}
