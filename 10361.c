  virtual void TabClosingAt(TabStripModel* tab_strip_model,
                            TabContentsWrapper* contents,
                            int index) {
    closing_count_++;
  }
