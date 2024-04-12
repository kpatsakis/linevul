base::RefCountedMemory* NTPResourceCache::GetNewTabHTML(WindowType win_type) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  if (win_type == GUEST) {
    if (!new_tab_guest_html_.get())
      CreateNewTabGuestHTML();
    return new_tab_guest_html_.get();
  } else if (win_type == INCOGNITO) {
    if (!new_tab_incognito_html_.get())
      CreateNewTabIncognitoHTML();
    return new_tab_incognito_html_.get();
  } else {
    if (NewTabCacheNeedsRefresh() || !new_tab_html_.get())
      CreateNewTabHTML();
    return new_tab_html_.get();
  }
}
