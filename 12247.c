int Browser::GetContentRestrictionsForSelectedTab() {
  int content_restrictions = 0;
  TabContents* current_tab = GetSelectedTabContents();
  if (current_tab) {
    content_restrictions = current_tab->content_restrictions();
    NavigationEntry* active_entry = current_tab->controller().GetActiveEntry();
    if (!SavePackage::IsSavableURL(active_entry ? active_entry->url() : GURL()))
      content_restrictions |= CONTENT_RESTRICTION_SAVE;
  }
  return content_restrictions;
}
