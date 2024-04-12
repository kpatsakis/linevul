bool TabStrip::OnMousePressed(const ui::MouseEvent& event) {
  UpdateStackedLayoutFromMouseEvent(this, event);
  return false;
}
