bool TabStripGtk::IsTabPinned(const TabGtk* tab) const {
  if (tab->closing())
    return false;

  return model_->IsTabPinned(GetIndexOfTab(tab));
}
