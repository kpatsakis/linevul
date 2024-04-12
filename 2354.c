void ContentSecurityPolicy::setupSelf(const SecurityOrigin& securityOrigin) {
  m_selfProtocol = securityOrigin.protocol();
  m_selfSource = new CSPSource(this, m_selfProtocol, securityOrigin.host(),
                               securityOrigin.port(), String(),
                               CSPSource::NoWildcard, CSPSource::NoWildcard);
}
