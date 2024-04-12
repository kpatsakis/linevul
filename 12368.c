void PDFiumEngine::LoadDocument() {
  if (!doc_ && !doc_loader_->IsDocumentComplete() &&
      !FPDFAvail_IsDocAvail(fpdf_availability_, &download_hints_)) {
    return;
  }

  if (getting_password_)
    return;

  ScopedUnsupportedFeature scoped_unsupported_feature(this);
  ScopedSubstFont scoped_subst_font(this);
  bool needs_password = false;
  if (TryLoadingDoc(std::string(), &needs_password)) {
    ContinueLoadingDocument(std::string());
    return;
  }
  if (needs_password)
    GetPasswordAndLoad();
  else
    client_->DocumentLoadFailed();
}
