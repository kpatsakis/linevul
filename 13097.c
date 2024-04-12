void PDFiumEngine::ZoomUpdated(double new_zoom_level) {
  CancelPaints();

  current_zoom_ = new_zoom_level;

  CalculateVisiblePages();
  UpdateTickMarks();
}
