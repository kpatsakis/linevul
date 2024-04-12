void WebLocalFrameImpl::ReportContentSecurityPolicyViolation(
    const blink::WebContentSecurityPolicyViolation& violation) {
  AddMessageToConsole(blink::WebConsoleMessage(
      WebConsoleMessage::kLevelError, violation.console_message,
      violation.source_location.url, violation.source_location.line_number,
      violation.source_location.column_number));

  std::unique_ptr<SourceLocation> source_location = SourceLocation::Create(
      violation.source_location.url, violation.source_location.line_number,
      violation.source_location.column_number, nullptr);

  DCHECK(GetFrame() && GetFrame()->GetDocument());
  Document* document = GetFrame()->GetDocument();
  Vector<String> report_endpoints;
  for (const WebString& end_point : violation.report_endpoints)
    report_endpoints.push_back(end_point);
  document->GetContentSecurityPolicy()->ReportViolation(
      violation.directive,
      ContentSecurityPolicy::GetDirectiveType(violation.effective_directive),
      violation.console_message, violation.blocked_url, report_endpoints,
      violation.use_reporting_api, violation.header,
      static_cast<ContentSecurityPolicyHeaderType>(violation.disposition),
      ContentSecurityPolicy::ViolationType::kURLViolation,
      std::move(source_location), nullptr /* LocalFrame */,
      violation.after_redirect ? RedirectStatus::kFollowedRedirect
                               : RedirectStatus::kNoRedirect,
      nullptr /* Element */);
}
