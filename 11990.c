void AutofillDialogViews::SuggestionView::SetIcon(
    const gfx::Image& image) {
  icon_->SetVisible(!image.IsEmpty());
  icon_->SetImage(image.AsImageSkia());
}
