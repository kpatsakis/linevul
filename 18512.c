void ContentSecurityPolicy::setOverrideURLForSelf(const KURL& url) {
  RefPtr<SecurityOrigin> origin = SecurityOrigin::create(url);
  m_selfProtocol = origin->protocol();
  m_selfSource =
      new CSPSource(this, m_selfProtocol, origin->host(), origin->port(),
                    String(), CSPSource::NoWildcard, CSPSource::NoWildcard);
}
