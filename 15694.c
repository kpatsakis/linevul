void InspectorPageAgent::deleteCookie(ErrorString*, const String& cookieName, const String& url)
{
    KURL parsedURL(ParsedURLString, url);
    for (Frame* frame = m_page->mainFrame(); frame; frame = frame->tree().traverseNext(m_page->mainFrame()))
        WebCore::deleteCookie(frame->document(), parsedURL, cookieName);
}
