WebPlugin* RenderView::CreateNPAPIPlugin(
    WebFrame* frame,
    const WebPluginParams& params,
    const FilePath& path,
    const std::string& mime_type) {
  return new webkit::npapi::WebPluginImpl(
      frame, params, path, mime_type, AsWeakPtr());
}
