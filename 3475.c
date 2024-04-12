void TabStrip::GenerateIdealBounds() {
  int new_tab_y = 0;

  if (touch_layout_.get()) {
    if (tabs_.view_size() == 0)
      return;

    int new_tab_x = tabs_.ideal_bounds(tabs_.view_size() - 1).right() +
        newtab_button_h_offset();
    newtab_button_bounds_.set_origin(gfx::Point(new_tab_x, new_tab_y));
    return;
  }

  double unselected, selected;
  GetDesiredTabWidths(tab_count(), GetMiniTabCount(), &unselected, &selected);
  current_unselected_width_ = unselected;
  current_selected_width_ = selected;

  int tab_height = Tab::GetStandardSize().height();
  int first_non_mini_index = 0;
  double tab_x = GenerateIdealBoundsForMiniTabs(&first_non_mini_index);
  for (int i = first_non_mini_index; i < tab_count(); ++i) {
    Tab* tab = tab_at(i);
    DCHECK(!tab->data().mini);
    double tab_width = tab->IsActive() ? selected : unselected;
    double end_of_tab = tab_x + tab_width;
    int rounded_tab_x = Round(tab_x);
    set_ideal_bounds(
        i,
        gfx::Rect(rounded_tab_x, 0, Round(end_of_tab) - rounded_tab_x,
                  tab_height));
    tab_x = end_of_tab + tab_h_offset();
  }

  int new_tab_x;
  if (abs(Round(unselected) - Tab::GetStandardSize().width()) > 1 &&
      !in_tab_close_) {
    new_tab_x = width() - newtab_button_bounds_.width();
  } else {
    new_tab_x = Round(tab_x - tab_h_offset()) + newtab_button_h_offset();
  }
  newtab_button_bounds_.set_origin(gfx::Point(new_tab_x, new_tab_y));
}
