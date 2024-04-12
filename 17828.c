void Tab::OnMouseReleased(const ui::MouseEvent& event) {
  controller_->OnMouseEventInTab(this, event);

  if (controller_->EndDrag(END_DRAG_COMPLETE))
    return;

  if (event.IsMiddleMouseButton()) {
    if (HitTestPoint(event.location())) {
      controller_->CloseTab(this, CLOSE_TAB_FROM_MOUSE);
    } else if (closing_) {
      gfx::Point location_in_parent = event.location();
      ConvertPointToTarget(this, parent(), &location_in_parent);
      Tab* closest_tab = controller_->GetTabAt(location_in_parent);
      if (closest_tab)
        controller_->CloseTab(closest_tab, CLOSE_TAB_FROM_MOUSE);
    }
  } else if (event.IsOnlyLeftMouseButton() && !event.IsShiftDown() &&
             !IsSelectionModifierDown(event)) {
    controller_->SelectTab(this, event);
  }
}
