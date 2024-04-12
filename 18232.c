Event* Document::createEvent(ExecutionContext* executionContext, const String& eventType, ExceptionState& exceptionState)
{
    Event* event = nullptr;
    for (const auto& factory : eventFactories()) {
        event = factory->create(executionContext, eventType);
        if (event)
            return event;
    }
    exceptionState.throwDOMException(NotSupportedError, "The provided event type ('" + eventType + "') is invalid.");
    return nullptr;
}
