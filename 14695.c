void BrowserView::RotatePaneFocus(bool forwards) {
  std::vector<views::AccessiblePaneView*> accessible_panes;
  GetAccessiblePanes(&accessible_panes);
  int pane_count = static_cast<int>(accessible_panes.size());
  int special_index = -1;

  std::vector<views::View*> accessible_views(
      accessible_panes.begin(), accessible_panes.end());
  accessible_views.push_back(GetTabContentsContainerView());
  if (devtools_container_->visible())
    accessible_views.push_back(devtools_container_);
  int count = static_cast<int>(accessible_views.size());

  const views::View* focused_view = GetFocusManager()->GetFocusedView();
  int index = -1;
  if (focused_view) {
    for (int i = 0; i < count; ++i) {
      if (accessible_views[i] == focused_view ||
          accessible_views[i]->Contains(focused_view)) {
        index = i;
        break;
      }
    }
  }

  if (focused_view && index >= pane_count)
    GetFocusManager()->StoreFocusedView();

#if defined(OS_CHROMEOS) && defined(USE_AURA)
  special_index = count;
  ++count;
#endif

  for (;;) {
    if (forwards)
      index = (index + 1) % count;
    else
      index = ((index - 1) + count) % count;

    if (index == special_index) {
#if defined(USE_ASH)
      ash::Shell::GetInstance()->RotateFocus(
          forwards ? ash::Shell::FORWARD : ash::Shell::BACKWARD);
#endif
      break;
    } else if (index < pane_count) {
      if (accessible_panes[index]->SetPaneFocusAndFocusDefault())
        break;
    } else {
      accessible_views[index]->RequestFocus();
      break;
    }
  }
}
