int PDFiumEngine::GetMostVisiblePage() {
  if (in_flight_visible_page_)
    return *in_flight_visible_page_;

  base::AutoReset<bool> defer_page_unload_guard(&defer_page_unload_, true);
  CalculateVisiblePages();
  return most_visible_page_;
}
