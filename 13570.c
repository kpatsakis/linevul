bool XSSAuditor::FilterInputToken(const FilterTokenRequest& request) {
  DCHECK_EQ(request.token.GetType(), HTMLToken::kStartTag);
  DCHECK(HasName(request.token, inputTag));

  return EraseAttributeIfInjected(request, formactionAttr, kURLWithUniqueOrigin,
                                  kSrcLikeAttributeTruncation);
}
