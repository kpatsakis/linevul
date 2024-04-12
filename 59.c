  virtual void Layout() {
    if (parent()) {
      gfx::Size ps = GetPreferredSize();
      SetBounds(parent()->width() - ps.width(),
                parent()->height() - ps.height(), ps.width(), ps.height());
    }
  }
