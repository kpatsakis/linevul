void AutofillPopupItemView::OnMouseEntered(const ui::MouseEvent& event) {
  AutofillPopupController* controller = popup_view_->controller();
  if (controller)
    controller->SetSelectedLine(line_number_);
}
