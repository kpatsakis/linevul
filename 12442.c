PaymentHandlerWebFlowViewController::CreateHeaderContentSeparatorView() {
  if (show_progress_bar_)
    return progress_bar_.get();
  return separator_.get();
}
