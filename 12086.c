bool TabStripGtk::IsTabDetached(const TabGtk* tab) const {
  if (drag_controller_.get())
    return drag_controller_->IsTabDetached(tab);
  return false;
}
