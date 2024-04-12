TabContents* TabStripModel::GetTabContentsAtImpl(int index) const {
  CHECK(ContainsIndex(index)) <<
      "Failed to find: " << index << " in: " << count() << " entries.";
  return TabContents::FromWebContents(contents_data_[index]->contents);
}
