void PDFiumEngine::Form_DisplayCaret(FPDF_FORMFILLINFO* param,
                                     FPDF_PAGE page,
                                     FPDF_BOOL visible,
                                     double left,
                                     double top,
                                     double right,
                                     double bottom) {
  PDFiumEngine* engine = static_cast<PDFiumEngine*>(param);
  engine->client_->UpdateCursor(PP_CURSORTYPE_IBEAM);
  std::vector<pp::Rect> tickmarks;
  pp::Rect rect(left, top, right, bottom);
  tickmarks.push_back(rect);
  engine->client_->UpdateTickMarks(tickmarks);
}
