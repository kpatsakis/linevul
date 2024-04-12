void TabStripModel::AddSelectionFromAnchorTo(int index) {
  int old_active = active_index();
  selection_model_.AddSelectionFromAnchorTo(index);
  NotifySelectionChanged(old_active);
}
