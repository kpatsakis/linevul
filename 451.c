bool FindInspectedBrowserAndTabIndex(
    WebContents* inspected_web_contents, Browser** browser, int* tab) {
  if (!inspected_web_contents)
    return false;

  for (auto* b : *BrowserList::GetInstance()) {
    int tab_index =
        b->tab_strip_model()->GetIndexOfWebContents(inspected_web_contents);
    if (tab_index != TabStripModel::kNoTab) {
      *browser = b;
      *tab = tab_index;
      return true;
    }
  }
  return false;
}
