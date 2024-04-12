void RenderWidgetHostViewAura::RenderViewGone(base::TerminationStatus status,
                                              int error_code) {
  UpdateCursorIfOverSelf();
  Destroy();
}
