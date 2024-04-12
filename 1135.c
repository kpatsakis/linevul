void PresentationConnection::didClose(
    WebPresentationConnectionCloseReason reason,
    const String& message) {
  if (m_state == WebPresentationConnectionState::Closed)
    return;

  m_state = WebPresentationConnectionState::Closed;
  dispatchStateChangeEvent(PresentationConnectionCloseEvent::create(
       EventTypeNames::close, connectionCloseReasonToString(reason), message));
 }
