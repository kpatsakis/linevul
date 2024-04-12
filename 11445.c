bool PresentationConnection::matches(const String& id, const KURL& url) const {
  return m_url == url && m_id == id;
}
