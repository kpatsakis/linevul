void Document::processHttpEquiv(const AtomicString& equiv, const AtomicString& content, bool inDocumentHeadElement)
{
    ASSERT(!equiv.isNull() && !content.isNull());

    if (equalIgnoringCase(equiv, "default-style")) {
        processHttpEquivDefaultStyle(content);
    } else if (equalIgnoringCase(equiv, "refresh")) {
        processHttpEquivRefresh(content);
    } else if (equalIgnoringCase(equiv, "set-cookie")) {
        processHttpEquivSetCookie(content);
    } else if (equalIgnoringCase(equiv, "content-language")) {
        setContentLanguage(content);
    } else if (equalIgnoringCase(equiv, "x-dns-prefetch-control")) {
        parseDNSPrefetchControlHeader(content);
    } else if (equalIgnoringCase(equiv, "x-frame-options")) {
        processHttpEquivXFrameOptions(content);
    } else if (equalIgnoringCase(equiv, "accept-ch")) {
        processHttpEquivAcceptCH(content);
    } else if (equalIgnoringCase(equiv, "content-security-policy") || equalIgnoringCase(equiv, "content-security-policy-report-only")) {
        if (inDocumentHeadElement)
            processHttpEquivContentSecurityPolicy(equiv, content);
        else
            contentSecurityPolicy()->reportMetaOutsideHead(content);
    }
}
