void PresentationConnection::terminate() {
  if (m_state != WebPresentationConnectionState::Connected)
    return;
  WebPresentationClient* client = presentationClient(getExecutionContext());
  if (client)
    client->terminateConnection(m_url, m_id);

  tearDown();
}
