blink::WebString RenderFrameImpl::UserAgentOverride() {
  if (!render_view_->webview() || !render_view_->webview()->MainFrame() ||
      render_view_->renderer_preferences_.user_agent_override.empty()) {
    return blink::WebString();
  }

  if (render_view_->webview()->MainFrame()->IsWebRemoteFrame())
    return blink::WebString();
  WebLocalFrame* main_frame =
      render_view_->webview()->MainFrame()->ToWebLocalFrame();

  WebDocumentLoader* document_loader = nullptr;
  if (main_frame->GetProvisionalDocumentLoader())
    document_loader = main_frame->GetProvisionalDocumentLoader();
  else
    document_loader = main_frame->GetDocumentLoader();

  InternalDocumentStateData* internal_data =
      document_loader
          ? InternalDocumentStateData::FromDocumentLoader(document_loader)
          : nullptr;
  if (internal_data && internal_data->is_overriding_user_agent())
    return WebString::FromUTF8(
        render_view_->renderer_preferences_.user_agent_override);
  return blink::WebString();
}
