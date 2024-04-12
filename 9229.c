void TabStripModel::AddSelectionFromAnchorTo(int index) {
  TabStripSelectionModel new_model;
  new_model.Copy(selection_model_);
  new_model.AddSelectionFromAnchorTo(index);
  SetSelection(new_model, NOTIFY_DEFAULT);
}
