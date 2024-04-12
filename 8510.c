bool PresentationConnection::matches(
    const WebPresentationSessionInfo& sessionInfo) const {
  return m_url == KURL(sessionInfo.url) && m_id == String(sessionInfo.id);
}
