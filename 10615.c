DocumentInit& DocumentInit::WithContextDocument(Document* context_document) {
  DCHECK(!context_document_);
  context_document_ = context_document;
  return *this;
}
