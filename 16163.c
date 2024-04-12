Event* Document::createEvent(ScriptState* script_state,
                             const String& event_type,
                             ExceptionState& exception_state) {
  Event* event = nullptr;
  ExecutionContext* execution_context = ExecutionContext::From(script_state);
  for (const auto& factory : EventFactories()) {
    event = factory->Create(execution_context, event_type);
    if (event) {
      if (DeprecatedEqualIgnoringCase(event_type, "TouchEvent") &&
          !OriginTrials::touchEventFeatureDetectionEnabled(execution_context))
        break;
      return event;
    }
  }
  exception_state.ThrowDOMException(
      kNotSupportedError,
      "The provided event type ('" + event_type + "') is invalid.");
  return nullptr;
}
