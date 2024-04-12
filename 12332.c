const AtomicString& connectionStateToString(
    WebPresentationConnectionState state) {
  DEFINE_STATIC_LOCAL(const AtomicString, connectingValue, ("connecting"));
  DEFINE_STATIC_LOCAL(const AtomicString, connectedValue, ("connected"));
  DEFINE_STATIC_LOCAL(const AtomicString, closedValue, ("closed"));
  DEFINE_STATIC_LOCAL(const AtomicString, terminatedValue, ("terminated"));

  switch (state) {
    case WebPresentationConnectionState::Connecting:
      return connectingValue;
    case WebPresentationConnectionState::Connected:
      return connectedValue;
    case WebPresentationConnectionState::Closed:
      return closedValue;
    case WebPresentationConnectionState::Terminated:
      return terminatedValue;
  }

  ASSERT_NOT_REACHED();
  return terminatedValue;
}
