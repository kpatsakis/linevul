bool ContentSecurityPolicy::allowFormAction(
    const KURL& url,
    RedirectStatus redirectStatus,
    SecurityViolationReportingPolicy reportingPolicy) const {
  return isAllowedByAll<&CSPDirectiveList::allowFormAction>(
      m_policies, url, redirectStatus, reportingPolicy);
}
