Document& Document::EnsureTemplateDocument() {
  if (IsTemplateDocument())
    return *this;

  if (template_document_)
    return *template_document_;

  if (IsHTMLDocument()) {
    template_document_ =
        HTMLDocument::Create(DocumentInit::Create()
                                 .WithContextDocument(ContextDocument())
                                 .WithURL(BlankURL())
                                 .WithNewRegistrationContext());
  } else {
    template_document_ =
        Document::Create(DocumentInit::Create().WithURL(BlankURL()));
  }

  template_document_->template_document_host_ = this;  // balanced in dtor.

  return *template_document_.Get();
}
