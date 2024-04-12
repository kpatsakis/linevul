  explicit ResizeLayoutAnimation(TabStripGtk* tabstrip)
      : TabAnimation(tabstrip, RESIZE) {
    int tab_count = tabstrip->GetTabCount();
    int mini_tab_count = tabstrip->GetMiniTabCount();
    GenerateStartAndEndWidths(tab_count, tab_count, mini_tab_count,
                              mini_tab_count);
    InitStartState();
  }
