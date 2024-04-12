void RenderWidgetHostImpl::ImeConfirmComposition(const string16& text) {
  ImeConfirmComposition(text, ui::Range::InvalidRange());
}
