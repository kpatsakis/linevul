void RenderWidgetHostViewGuest::RenderViewGone(base::TerminationStatus status,
                                               int error_code) {
  Destroy();
}
