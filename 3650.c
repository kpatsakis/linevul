const views::View* TabStrip::GetViewByID(int view_id) const {
  if (tab_count() > 0) {
    if (view_id == VIEW_ID_TAB_LAST) {
      return tab_at(tab_count() - 1);
    } else if ((view_id >= VIEW_ID_TAB_0) && (view_id < VIEW_ID_TAB_LAST)) {
      int index = view_id - VIEW_ID_TAB_0;
      if (index >= 0 && index < tab_count()) {
        return tab_at(index);
      } else {
        return NULL;
      }
    }
  }

  return View::GetViewByID(view_id);
}
