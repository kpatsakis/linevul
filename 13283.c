bool TabStripGtk::CanPaintOnlyFavicons(const GdkRectangle* rects,
    int num_rects, std::vector<int>* tabs_to_paint) {
  int t = 0;
  for (int r = 0; r < num_rects; ++r) {
    while (t < GetTabCount()) {
      TabGtk* tab = GetTabAt(t);
      if (GdkRectMatchesTabFaviconBounds(rects[r], tab) &&
          tab->ShouldShowIcon()) {
        tabs_to_paint->push_back(t);
        ++t;
        break;
      }
      ++t;
    }
  }
  return static_cast<int>(tabs_to_paint->size()) == num_rects;
}
