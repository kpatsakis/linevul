void AutofillDialogViews::UpdateButtonStripExtraView() {
  save_in_chrome_checkbox_container_->SetVisible(
      delegate_->ShouldOfferToSaveInChrome());

  gfx::Image image = delegate_->ButtonStripImage();
  button_strip_image_->SetVisible(!image.IsEmpty());
  button_strip_image_->SetImage(image.AsImageSkia());
}
