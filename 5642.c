std::string PDFiumEngine::GetLinkAtPosition(const pp::Point& point) {
  std::string url;
  int temp;
  int page_index = -1;
  int form_type = FPDF_FORMFIELD_UNKNOWN;
  PDFiumPage::LinkTarget target;
  PDFiumPage::Area area =
      GetCharIndex(point, &page_index, &temp, &form_type, &target);
  if (area == PDFiumPage::WEBLINK_AREA)
    url = target.url;
  return url;
}
