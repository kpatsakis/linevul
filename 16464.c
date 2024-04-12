int PDFiumEngine::GetNamedDestinationPage(const std::string& destination) {
  FPDF_DEST dest = FPDF_GetNamedDestByName(doc_, destination.c_str());
  if (!dest) {
    base::string16 destination_wide = base::UTF8ToUTF16(destination);
    FPDF_WIDESTRING destination_pdf_wide =
        reinterpret_cast<FPDF_WIDESTRING>(destination_wide.c_str());
    FPDF_BOOKMARK bookmark = FPDFBookmark_Find(doc_, destination_pdf_wide);
    if (!bookmark)
      return -1;
    dest = FPDFBookmark_GetDest(doc_, bookmark);
  }
  return dest ? FPDFDest_GetPageIndex(doc_, dest) : -1;
}
