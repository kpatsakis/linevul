const AtomicString& PresentationConnection::state() const {
  return connectionStateToString(m_state);
}
