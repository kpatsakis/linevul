  void UpdateMapping() {
    count_ = XGetPointerMapping(ui::GetXDisplay(), map_, arraysize(map_));
  }
