void AppResult::ExtensionEnableFlowFinished() {
  extension_enable_flow_.reset();
  controller_->OnCloseChildDialog();

  Open(ui::EF_NONE);
}
