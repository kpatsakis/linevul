bool PDFiumEngineExports::GetPDFPageSizeByIndex(const void* pdf_buffer,
                                                int pdf_buffer_size,
                                                int page_number,
                                                double* width,
                                                double* height) {
  FPDF_DOCUMENT doc =
      FPDF_LoadMemDocument(pdf_buffer, pdf_buffer_size, nullptr);
  if (!doc)
    return false;
  bool success = FPDF_GetPageSizeByIndex(doc, page_number, width, height) != 0;
  FPDF_CloseDocument(doc);
  return success;
}
