DocumentInit& DocumentInit::WithOwnerDocument(Document* owner_document) {
  DCHECK(!owner_document_);
  owner_document_ = owner_document;
  return *this;
}
