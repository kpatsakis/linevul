WebContents* TabStripModel::GetActiveWebContents() const {
  return GetWebContentsAt(active_index());
}
