void FrameFetchContext::ProvideDocumentToContext(FetchContext& context,
                                                 Document* document) {
  DCHECK(document);
  CHECK(context.IsFrameFetchContext());
  static_cast<FrameFetchContext&>(context).document_ = document;
  static_cast<FrameFetchContext&>(context).fetch_client_settings_object_ =
      new FetchClientSettingsObjectImpl(*document);
}
