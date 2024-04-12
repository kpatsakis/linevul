void ContentSecurityPolicy::DispatchViolationEvents(
    const SecurityPolicyViolationEventInit* violation_data,
    Element* element) {
  if (execution_context_->IsWorkletGlobalScope())
    return;

  SecurityPolicyViolationEvent& event = *SecurityPolicyViolationEvent::Create(
      event_type_names::kSecuritypolicyviolation, violation_data);
  DCHECK(event.bubbles());

  if (auto* document = DynamicTo<Document>(*execution_context_)) {
    if (element && element->isConnected() && element->GetDocument() == document)
      element->EnqueueEvent(event, TaskType::kInternalDefault);
    else
      document->EnqueueEvent(event, TaskType::kInternalDefault);
  } else if (auto* scope = DynamicTo<WorkerGlobalScope>(*execution_context_)) {
    scope->EnqueueEvent(event, TaskType::kInternalDefault);
  }
}
