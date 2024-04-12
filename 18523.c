bool ContentSecurityPolicy::allowStyleFromSource(
    const KURL& url,
    const String& nonce,
    RedirectStatus redirectStatus,
    SecurityViolationReportingPolicy reportingPolicy) const {
  if (shouldBypassContentSecurityPolicy(url, SchemeRegistry::PolicyAreaStyle))
    return true;
  return isAllowedByAll<&CSPDirectiveList::allowStyleFromSource>(
      m_policies, url, nonce, redirectStatus, reportingPolicy);
}
