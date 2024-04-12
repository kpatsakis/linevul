void InspectorPageAgent::getResourceContent(ErrorString* errorString, const String& frameId, const String& url, String* content, bool* base64Encoded)
{
    Frame* frame = assertFrame(errorString, frameId);
    if (!frame)
        return;
    resourceContent(errorString, frame, KURL(ParsedURLString, url), content, base64Encoded);
}
