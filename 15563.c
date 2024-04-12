bool PDFiumEngineExports::RenderPDFPageToBitmap(
    const void* pdf_buffer,
    int pdf_buffer_size,
    int page_number,
    const RenderingSettings& settings,
    void* bitmap_buffer) {
  FPDF_DOCUMENT doc =
      FPDF_LoadMemDocument(pdf_buffer, pdf_buffer_size, nullptr);
  if (!doc)
    return false;
  FPDF_PAGE page = FPDF_LoadPage(doc, page_number);
  if (!page) {
    FPDF_CloseDocument(doc);
    return false;
  }

  pp::Rect dest;
  int rotate = CalculatePosition(page, settings, &dest);

  FPDF_BITMAP bitmap =
      FPDFBitmap_CreateEx(settings.bounds.width(), settings.bounds.height(),
                          FPDFBitmap_BGRA, bitmap_buffer,
                          settings.bounds.width() * 4);
  FPDFBitmap_FillRect(bitmap, 0, 0, settings.bounds.width(),
                      settings.bounds.height(), 0xFFFFFFFF);
  dest.set_point(dest.point() - settings.bounds.point());
  FPDF_RenderPageBitmap(
      bitmap, page, dest.x(), dest.y(), dest.width(), dest.height(), rotate,
      FPDF_ANNOT | FPDF_PRINTING | FPDF_NO_CATCH);
  FPDFBitmap_Destroy(bitmap);
  FPDF_ClosePage(page);
  FPDF_CloseDocument(doc);
  return true;
}
