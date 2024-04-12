void ContentSecurityPolicy::BindToExecutionContext(
    ExecutionContext* execution_context) {
  execution_context_ = execution_context;
  ApplyPolicySideEffectsToExecutionContext();
}
