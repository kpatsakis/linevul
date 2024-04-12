bool PDFiumEngine::OnMouseUp(const pp::MouseInputEvent& event) {
  if (event.GetButton() != PP_INPUTEVENT_MOUSEBUTTON_LEFT &&
      event.GetButton() != PP_INPUTEVENT_MOUSEBUTTON_MIDDLE) {
    return false;
  }

  if (event.GetButton() == PP_INPUTEVENT_MOUSEBUTTON_LEFT)
    SetMouseLeftButtonDown(false);

  int page_index = -1;
  int char_index = -1;
  int form_type = FPDF_FORMFIELD_UNKNOWN;
  PDFiumPage::LinkTarget target;
  pp::Point point = event.GetPosition();
  PDFiumPage::Area area =
      GetCharIndex(point, &page_index, &char_index, &form_type, &target);

  if (mouse_down_state_.Matches(area, target)) {
    if (area == PDFiumPage::WEBLINK_AREA) {
      uint32_t modifiers = event.GetModifiers();
      bool middle_button =
          !!(modifiers & PP_INPUTEVENT_MODIFIER_MIDDLEBUTTONDOWN);
      bool alt_key = !!(modifiers & PP_INPUTEVENT_MODIFIER_ALTKEY);
      bool ctrl_key = !!(modifiers & PP_INPUTEVENT_MODIFIER_CONTROLKEY);
      bool meta_key = !!(modifiers & PP_INPUTEVENT_MODIFIER_METAKEY);
      bool shift_key = !!(modifiers & PP_INPUTEVENT_MODIFIER_SHIFTKEY);

      WindowOpenDisposition disposition = ui::DispositionFromClick(
          middle_button, alt_key, ctrl_key, meta_key, shift_key);

      client_->NavigateTo(target.url, disposition);
      SetInFormTextArea(false);
      return true;
    }
    if (area == PDFiumPage::DOCLINK_AREA) {
      pp::Rect page_rect(GetPageScreenRect(target.page));
      int y = position_.y() + page_rect.y();
      if (target.y_in_pixels)
        y += target.y_in_pixels.value() * current_zoom_;
      client_->ScrollToY(y, /*compensate_for_toolbar=*/true);
      SetInFormTextArea(false);
      return true;
    }
  }

  if (event.GetButton() == PP_INPUTEVENT_MOUSEBUTTON_MIDDLE)
    return false;

  if (page_index != -1) {
    double page_x;
    double page_y;
    DeviceToPage(page_index, point.x(), point.y(), &page_x, &page_y);
    FORM_OnLButtonUp(form_, pages_[page_index]->GetPage(), 0, page_x, page_y);
  }

  if (!selecting_)
    return false;

  SetSelecting(false);
  return true;
}
