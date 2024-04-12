LoginDisplayHostWebUI::LoginDisplayHostWebUI()
    : oobe_startup_sound_played_(StartupUtils::IsOobeCompleted()),
      weak_factory_(this) {
  if (!features::IsAshInBrowserProcess()) {
    finalize_animation_type_ = ANIMATION_NONE;
    initialize_webui_hidden_ = false;
  }

  DBusThreadManager::Get()->GetSessionManagerClient()->AddObserver(this);
  CrasAudioHandler::Get()->AddAudioObserver(this);

  display::Screen::GetScreen()->AddObserver(this);

  ui::InputDeviceManager::GetInstance()->AddObserver(this);

  registrar_.Add(this, chrome::NOTIFICATION_LOGIN_USER_CHANGED,
                 content::NotificationService::AllSources());

  bool zero_delay_enabled = WizardController::IsZeroDelayEnabled();
  if (!features::IsAshInBrowserProcess())
    zero_delay_enabled = true;

  waiting_for_wallpaper_load_ = !zero_delay_enabled;

  if (features::IsAshInBrowserProcess()) {
    initialize_webui_hidden_ =
        kHiddenWebUIInitializationDefault && !zero_delay_enabled;
  }

  if (features::IsAshInBrowserProcess() &&
      base::CommandLine::ForCurrentProcess()->HasSwitch(
          switches::kAshWebUIInit)) {
    const std::string override_type =
        base::CommandLine::ForCurrentProcess()->GetSwitchValueASCII(
            switches::kAshWebUIInit);
    if (override_type == kWebUIInitParallel)
      initialize_webui_hidden_ = true;
    else if (override_type == kWebUIInitPostpone)
      initialize_webui_hidden_ = false;
  }

  if (!StartupUtils::IsOobeCompleted())
    initialize_webui_hidden_ = false;

  if (waiting_for_wallpaper_load_) {
    registrar_.Add(this, chrome::NOTIFICATION_WALLPAPER_ANIMATION_FINISHED,
                   content::NotificationService::AllSources());
  }

  if (waiting_for_wallpaper_load_ && initialize_webui_hidden_) {
    registrar_.Add(this, chrome::NOTIFICATION_LOGIN_OR_LOCK_WEBUI_VISIBLE,
                   content::NotificationService::AllSources());
    registrar_.Add(this, chrome::NOTIFICATION_LOGIN_NETWORK_ERROR_SHOWN,
                   content::NotificationService::AllSources());
  }
  VLOG(1) << "Login WebUI >> "
          << "zero_delay: " << zero_delay_enabled
          << " wait_for_wp_load_: " << waiting_for_wallpaper_load_
          << " init_webui_hidden_: " << initialize_webui_hidden_;

  media::SoundsManager* manager = media::SoundsManager::Get();
  ui::ResourceBundle& bundle = ui::ResourceBundle::GetSharedInstance();
  manager->Initialize(SOUND_STARTUP,
                      bundle.GetRawDataResource(IDR_SOUND_STARTUP_WAV));

  login_display_ = std::make_unique<LoginDisplayWebUI>();
}
