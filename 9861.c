bool XSSAuditor::FilterObjectToken(const FilterTokenRequest& request) {
  DCHECK_EQ(request.token.GetType(), HTMLToken::kStartTag);
  DCHECK(HasName(request.token, objectTag));

  bool did_block_script = false;
  if (IsContainedInRequest(CanonicalizedSnippetForTagName(request))) {
    did_block_script |= EraseAttributeIfInjected(
        request, dataAttr, BlankURL().GetString(), kSrcLikeAttributeTruncation);
    did_block_script |= EraseAttributeIfInjected(request, typeAttr);
    did_block_script |= EraseAttributeIfInjected(request, classidAttr);
  }
  return did_block_script;
}
