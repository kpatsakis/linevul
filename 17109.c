bool XSSAuditor::filterFrameToken(const FilterTokenRequest& request)
{
    ASSERT(request.token.type() == HTMLToken::StartTag);
    ASSERT(hasName(request.token, iframeTag) || hasName(request.token, frameTag));

    bool didBlockScript = eraseAttributeIfInjected(request, srcdocAttr, String(), ScriptLikeAttribute);
    if (isContainedInRequest(decodedSnippetForName(request)))
        didBlockScript |= eraseAttributeIfInjected(request, srcAttr, String(), SrcLikeAttribute);

    return didBlockScript;
}
