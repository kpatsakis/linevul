void ChromePasswordManagerClient::HidePasswordGenerationPopup() {
  if (popup_controller_)
    popup_controller_->HideAndDestroy();
}
