bool ContentSecurityPolicy::allowJavaScriptURLs(
    Element* element,
    const String& source,
    const String& contextURL,
    const WTF::OrdinalNumber& contextLine,
    SecurityViolationReportingPolicy reportingPolicy) const {
  return isAllowedByAll<&CSPDirectiveList::allowJavaScriptURLs>(
      m_policies, element, source, contextURL, contextLine, reportingPolicy);
}
