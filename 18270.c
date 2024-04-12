PaymentHandlerWebFlowViewController::GetHeaderBackground() {
  auto default_header_background =
      PaymentRequestSheetController::GetHeaderBackground();
  if (web_contents()) {
    return views::CreateSolidBackground(color_utils::GetResultingPaintColor(
        web_contents()->GetThemeColor().value_or(SK_ColorTRANSPARENT),
        default_header_background->get_color()));
  }
  return default_header_background;
}
