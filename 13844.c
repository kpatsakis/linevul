bool XSSAuditor::FilterLinkToken(const FilterTokenRequest& request) {
  DCHECK_EQ(request.token.GetType(), HTMLToken::kStartTag);
  DCHECK(HasName(request.token, linkTag));

  size_t index_of_attribute = 0;
  if (!FindAttributeWithName(request.token, relAttr, index_of_attribute))
    return false;

  const HTMLToken::Attribute& attribute =
      request.token.Attributes().at(index_of_attribute);
  LinkRelAttribute parsed_attribute(attribute.Value());
  if (!parsed_attribute.IsImport())
    return false;

  return EraseAttributeIfInjected(request, hrefAttr, kURLWithUniqueOrigin,
                                  kSrcLikeAttributeTruncation,
                                  kAllowSameOriginHref);
}
