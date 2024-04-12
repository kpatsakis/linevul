bool TabStrip::OnMousePressed(const ui::MouseEvent& event) {
  UpdateLayoutTypeFromMouseEvent(this, event);
  return false;
}
