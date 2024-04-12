LocalFrame* DocumentInit::GetFrame() const {
  return document_loader_ ? document_loader_->GetFrame() : nullptr;
}
