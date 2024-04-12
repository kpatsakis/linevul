void TabStripGtk::UpdateDropIndex(GdkDragContext* context, gint x, gint y) {
  x = gtk_util::MirroredXCoordinate(tabstrip_.get(), x);
  for (int i = GetMiniTabCount(); i < GetTabCount(); ++i) {
    TabGtk* tab = GetTabAt(i);
    gfx::Rect bounds = tab->GetNonMirroredBounds(tabstrip_.get());
    const int tab_max_x = bounds.x() + bounds.width();
    const int hot_width = bounds.width() / kTabEdgeRatioInverse;
    if (x < tab_max_x) {
      if (x < bounds.x() + hot_width)
        SetDropIndex(i, true);
      else if (x >= tab_max_x - hot_width)
        SetDropIndex(i + 1, true);
      else
        SetDropIndex(i, false);
      return;
    }
  }

  SetDropIndex(GetTabCount(), true);
}
