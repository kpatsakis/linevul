void AutofillPopupRowView::SetSelected(bool is_selected) {
  if (is_selected == is_selected_)
    return;

  is_selected_ = is_selected;
  NotifyAccessibilityEvent(ax::mojom::Event::kSelection, true);
  RefreshStyle();
}
