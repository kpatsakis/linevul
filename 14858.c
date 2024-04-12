bool canLoadURL(const KURL& url, const ContentType& contentType) {
  DEFINE_STATIC_LOCAL(const String, codecs, ("codecs"));

  String contentMIMEType = contentType.type().lower();
  String contentTypeCodecs = contentType.parameter(codecs);

  if (contentMIMEType.isEmpty() ||
      contentMIMEType == "application/octet-stream" ||
      contentMIMEType == "text/plain") {
    if (url.protocolIsData())
      contentMIMEType = mimeTypeFromDataURL(url.getString());
  }

  if (contentMIMEType.isEmpty())
    return true;

  if (contentMIMEType != "application/octet-stream" ||
      contentTypeCodecs.isEmpty()) {
    return MIMETypeRegistry::supportsMediaMIMEType(contentMIMEType,
                                                   contentTypeCodecs);
  }

  return false;
}
