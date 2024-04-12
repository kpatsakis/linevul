bool XSSAuditor::FilterScriptToken(const FilterTokenRequest& request) {
  DCHECK_EQ(request.token.GetType(), HTMLToken::kStartTag);
  DCHECK(HasName(request.token, scriptTag));

  bool did_block_script = false;
  script_tag_found_in_request_ =
      IsContainedInRequest(CanonicalizedSnippetForTagName(request));
  if (script_tag_found_in_request_) {
    did_block_script |= EraseAttributeIfInjected(
        request, srcAttr, BlankURL().GetString(), kSrcLikeAttributeTruncation);
    did_block_script |= EraseAttributeIfInjected(request, SVGNames::hrefAttr,
                                                 BlankURL().GetString(),
                                                 kSrcLikeAttributeTruncation);
    did_block_script |= EraseAttributeIfInjected(request, XLinkNames::hrefAttr,
                                                 BlankURL().GetString(),
                                                 kSrcLikeAttributeTruncation);
  }
  return did_block_script;
}
