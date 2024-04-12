void TaskManagerView::Layout() {
  const int kTableButtonSpacing = 12;

  gfx::Size size = kill_button_->GetPreferredSize();
  int prefered_width = size.width();
  int prefered_height = size.height();

  tab_table_->SetBounds(
      x() + views::kPanelHorizMargin,
      y() + views::kPanelVertMargin,
      width() - 2 * views::kPanelHorizMargin,
      height() - 2 * views::kPanelVertMargin - prefered_height);

  gfx::Rect parent_bounds = parent()->GetContentsBounds();
  int y_buttons =
      parent_bounds.bottom() - prefered_height - views::kButtonVEdgeMargin;

  kill_button_->SetBounds(
      x() + width() - prefered_width - views::kPanelHorizMargin,
      y_buttons,
      prefered_width,
      prefered_height);

  if (purge_memory_button_) {
    size = purge_memory_button_->GetPreferredSize();
    purge_memory_button_->SetBounds(
        kill_button_->x() - size.width() -
            views::kUnrelatedControlHorizontalSpacing,
        y_buttons, size.width(), size.height());
  }

  size = about_memory_link_->GetPreferredSize();
  int link_prefered_width = size.width();
  int link_prefered_height = size.height();
  int link_y_offset = std::max(0, prefered_height - link_prefered_height) / 2;
  about_memory_link_->SetBounds(
      x() + views::kPanelHorizMargin,
      y_buttons + prefered_height - link_prefered_height - link_y_offset,
      link_prefered_width,
      link_prefered_height);
}
