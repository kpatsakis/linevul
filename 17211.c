bool WebPageSerializer::serialize(WebLocalFrame* frame,
                                  WebPageSerializerClient* client,
                                  const WebVector<WebURL>& links,
                                  const WebVector<WebString>& localPaths,
                                  const WebString& localDirectoryName)
{
    WebPageSerializerImpl serializerImpl(
        frame, client, links, localPaths, localDirectoryName);
    return serializerImpl.serialize();
}
