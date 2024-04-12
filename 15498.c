void PDFiumEngine::OnDocumentComplete() {
  if (!doc_ || !form_) {
    file_access_.m_FileLen = doc_loader_.document_size();
    if (!fpdf_availability_) {
      fpdf_availability_ = FPDFAvail_Create(&file_availability_, &file_access_);
      DCHECK(fpdf_availability_);
    }
    LoadDocument();
    return;
  }

  FinishLoadingDocument();
}
