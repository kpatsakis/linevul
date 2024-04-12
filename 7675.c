bool ContentSecurityPolicy::AllowInlineStyle(
    Element* element,
    const String& context_url,
    const String& nonce,
    const WTF::OrdinalNumber& context_line,
    const String& style_content,
    InlineType inline_type,
    SecurityViolationReportingPolicy reporting_policy) const {
  DCHECK(element);

  if (override_inline_style_allowed_)
    return true;

  Vector<CSPHashValue> csp_hash_values;
  FillInCSPHashValues(style_content, style_hash_algorithms_used_,
                      &csp_hash_values);

  bool is_allowed = true;
  for (const auto& policy : policies_) {
    is_allowed &=
        CheckStyleHashAgainstPolicy(csp_hash_values, policy, inline_type) ||
        policy->AllowInlineStyle(element, context_url, nonce, context_line,
                                 reporting_policy, style_content, inline_type);
  }

  return is_allowed;
}
