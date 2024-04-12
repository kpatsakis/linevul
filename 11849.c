bool isAllowedByAll(const CSPDirectiveListVector& policies,
                    const KURL& url,
                    const String& nonce,
                    RedirectStatus redirectStatus,
                    SecurityViolationReportingPolicy reportingPolicy) {
  if (ContentSecurityPolicy::shouldBypassContentSecurityPolicy(url))
    return true;

  bool isAllowed = true;
  for (const auto& policy : policies) {
    isAllowed &= (policy.get()->*allowFromURLWithNonce)(
        url, nonce, redirectStatus, reportingPolicy);
  }
  return isAllowed;
}
