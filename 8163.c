void ChromePasswordManagerClient::LogFirstFillingResult(
    uint32_t form_renderer_id,
    int32_t result) {
  auto* driver = driver_factory_->GetDriverForFrame(
      password_manager_driver_bindings_.GetCurrentTargetFrame());
  GetPasswordManager()->LogFirstFillingResult(driver, form_renderer_id, result);
}
