void TabStripGtk::ReStack() {
  TRACE_EVENT0("ui::gtk", "TabStripGtk::ReStack");

  if (!gtk_widget_get_realized(tabstrip_.get())) {
    return;
  }
  int tab_count = GetTabCount();
  TabGtk* active_tab = NULL;
  for (int i = tab_count - 1; i >= 0; --i) {
    TabGtk* tab = GetTabAt(i);
    if (tab->IsActive())
      active_tab = tab;
    else
      tab->Raise();
  }
  if (active_tab)
    active_tab->Raise();
}
