void TabStrip::PaintChildren(const views::PaintInfo& paint_info) {
  bool is_dragging = false;
  Tab* active_tab = nullptr;
  Tabs tabs_dragging;
  Tabs selected_and_hovered_tabs;

  const auto paint_or_add_to_tabs = [&paint_info,
                                     &selected_and_hovered_tabs](Tab* tab) {
    if (tab->tab_style()->GetZValue() > 0.0) {
      selected_and_hovered_tabs.push_back(tab);
    } else {
      tab->Paint(paint_info);
    }
  };

  const auto paint_closing_tabs = [=](int index) {
    if (tabs_closing_map_.find(index) == tabs_closing_map_.end())
      return;
    for (Tab* tab : base::Reversed(tabs_closing_map_[index]))
      paint_or_add_to_tabs(tab);
  };

  paint_closing_tabs(tab_count());

  int active_tab_index = -1;
  for (int i = tab_count() - 1; i >= 0; --i) {
    Tab* tab = tab_at(i);
    if (tab->dragging() && !stacked_layout_) {
      is_dragging = true;
      if (tab->IsActive()) {
        active_tab = tab;
        active_tab_index = i;
      } else {
        tabs_dragging.push_back(tab);
      }
    } else if (tab->IsActive()) {
      active_tab = tab;
      active_tab_index = i;
    } else if (!stacked_layout_) {
      paint_or_add_to_tabs(tab);
    }
    paint_closing_tabs(i);
  }

  if (stacked_layout_ && active_tab_index >= 0) {
    for (int i = 0; i < active_tab_index; ++i) {
      Tab* tab = tab_at(i);
      tab->Paint(paint_info);
    }

    for (int i = tab_count() - 1; i > active_tab_index; --i) {
      Tab* tab = tab_at(i);
      tab->Paint(paint_info);
    }
  }

  std::stable_sort(selected_and_hovered_tabs.begin(),
                   selected_and_hovered_tabs.end(), [](Tab* tab1, Tab* tab2) {
                     return tab1->tab_style()->GetZValue() <
                            tab2->tab_style()->GetZValue();
                   });
  for (Tab* tab : selected_and_hovered_tabs)
    tab->Paint(paint_info);

  for (const auto& header_pair : group_headers_)
    header_pair.second->Paint(paint_info);

  if (active_tab && !is_dragging)
    active_tab->Paint(paint_info);

  if (!new_tab_button_->layer())
    new_tab_button_->Paint(paint_info);

  for (size_t i = 0; i < tabs_dragging.size(); ++i)
    tabs_dragging[i]->Paint(paint_info);

  if (active_tab && is_dragging)
    active_tab->Paint(paint_info);
}
