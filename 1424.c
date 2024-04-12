bool TabStripModel::IsTabPinned(int index) const {
  DCHECK(ContainsIndex(index));
  return contents_data_[index]->pinned;
}
