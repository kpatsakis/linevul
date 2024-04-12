void PresentationConnection::addedEventListener(
    const AtomicString& eventType,
    RegisteredEventListener& registeredListener) {
  EventTargetWithInlineData::addedEventListener(eventType, registeredListener);
  if (eventType == EventTypeNames::connect)
    UseCounter::count(getExecutionContext(),
                      UseCounter::PresentationConnectionConnectEventListener);
  else if (eventType == EventTypeNames::close)
    UseCounter::count(getExecutionContext(),
                      UseCounter::PresentationConnectionCloseEventListener);
  else if (eventType == EventTypeNames::terminate)
    UseCounter::count(getExecutionContext(),
                      UseCounter::PresentationConnectionTerminateEventListener);
  else if (eventType == EventTypeNames::message)
    UseCounter::count(getExecutionContext(),
                      UseCounter::PresentationConnectionMessageEventListener);
}
