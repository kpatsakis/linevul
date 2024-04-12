void ShowLoginWizardFinish(
    chromeos::OobeScreen first_screen,
    const chromeos::StartupCustomizationDocument* startup_manifest) {
  TRACE_EVENT0("chromeos", "ShowLoginWizard::ShowLoginWizardFinish");


  chromeos::LoginDisplayHost* display_host = nullptr;
  if (chromeos::LoginDisplayHost::default_host()) {
    display_host = chromeos::LoginDisplayHost::default_host();
  } else if (ash::features::IsViewsLoginEnabled() &&
             ShouldShowSigninScreen(first_screen)) {
    display_host = new chromeos::LoginDisplayHostMojo();
  } else {
    display_host = new chromeos::LoginDisplayHostWebUI();
  }

  std::string timezone;
  if (chromeos::system::PerUserTimezoneEnabled()) {
    timezone = g_browser_process->local_state()->GetString(
        prefs::kSigninScreenTimezone);
  }

  if (ShouldShowSigninScreen(first_screen)) {
    display_host->StartSignInScreen(chromeos::LoginScreenContext());
  } else {
    display_host->StartWizard(first_screen);

    const std::string customization_timezone =
        startup_manifest->initial_timezone();
    VLOG(1) << "Initial time zone: " << customization_timezone;
    if (!customization_timezone.empty())
      timezone = customization_timezone;
  }
  if (!timezone.empty()) {
    chromeos::system::SetSystemAndSigninScreenTimezone(timezone);
  }
}
