void PDFiumEngine::AppendBlankPages(int num_pages) {
  DCHECK_NE(num_pages, 0);

  if (!doc_)
    return;

  selection_.clear();
  pending_pages_.clear();

  while (pages_.size() > 1) {
    delete pages_.back();
    pages_.pop_back();
    FPDFPage_Delete(doc_, pages_.size());
  }

  std::vector<pp::Rect> page_rects;
  pp::Size page_size = GetPageSize(0);
  page_size.Enlarge(kPageShadowLeft + kPageShadowRight,
                    kPageShadowTop + kPageShadowBottom);
  pp::Size old_document_size = document_size_;
  document_size_ = pp::Size(page_size.width(), 0);
  for (int i = 0; i < num_pages; ++i) {
    if (i != 0) {
      document_size_.Enlarge(0, kPageSeparatorThickness);
    }

    pp::Rect rect(pp::Point(0, document_size_.height()), page_size);
    page_rects.push_back(rect);

    document_size_.Enlarge(0, page_size.height());
  }

  for (int i = 1; i < num_pages; ++i) {
    pp::Rect page_rect(page_rects[i]);
    page_rect.Inset(kPageShadowLeft, kPageShadowTop,
                    kPageShadowRight, kPageShadowBottom);
    double width_in_points = ConvertUnitDouble(page_rect.width(),
                                               kPixelsPerInch,
                                               kPointsPerInch);
    double height_in_points = ConvertUnitDouble(page_rect.height(),
                                                kPixelsPerInch,
                                                kPointsPerInch);
    FPDFPage_New(doc_, i, width_in_points, height_in_points);
    pages_.push_back(new PDFiumPage(this, i, page_rect, true));
  }

  CalculateVisiblePages();
  if (document_size_ != old_document_size)
    client_->DocumentSizeUpdated(document_size_);
}
