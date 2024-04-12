ObjectContentType WebFrameLoaderClient::objectContentType(
    const KURL& url,
    const String& explicit_mime_type) {

  String mime_type = explicit_mime_type;
  if (mime_type.isEmpty()) {
    String filename = url.lastPathComponent();
    int extension_pos = filename.reverseFind('.');
    if (extension_pos >= 0)
      mime_type = MIMETypeRegistry::getMIMETypeForPath(url.path());

    if (mime_type.isEmpty())
      return ObjectContentFrame;
  }

  if (MIMETypeRegistry::isSupportedImageMIMEType(mime_type))
    return ObjectContentImage;

  PluginData* plugin_data = webframe_->frame()->page()->pluginData();
  if (plugin_data && plugin_data->supportsMimeType(mime_type))
    return ObjectContentNetscapePlugin;

  if (MIMETypeRegistry::isSupportedNonImageMIMEType(mime_type))
    return ObjectContentFrame;

  return ObjectContentNone;
}
