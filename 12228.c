void ChromeBrowserMainPartsChromeos::PreMainMessageLoopRun() {
  TPMTokenLoader::Get()->SetCryptoTaskRunner(
      content::BrowserThread::GetTaskRunnerForThread(
          content::BrowserThread::IO));

  system_token_certdb_initializer_ =
      std::make_unique<internal::SystemTokenCertDBInitializer>();
  system_token_certdb_initializer_->Initialize();

  CrasAudioHandler::Initialize(
      new AudioDevicesPrefHandlerImpl(g_browser_process->local_state()));

  content::MediaCaptureDevices::GetInstance()->AddVideoCaptureObserver(
      CrasAudioHandler::Get());

  quirks::QuirksManager::Initialize(
      std::unique_ptr<quirks::QuirksManager::Delegate>(
          new quirks::QuirksManagerDelegateImpl()),
      g_browser_process->local_state(),
      g_browser_process->system_request_context());

  bool load_oem_statistics = !StartupUtils::IsOobeCompleted();
  system::StatisticsProvider::GetInstance()->StartLoadingMachineStatistics(
      load_oem_statistics);

  base::FilePath downloads_directory;
  CHECK(base::PathService::Get(chrome::DIR_DEFAULT_DOWNLOADS,
                               &downloads_directory));

  DeviceOAuth2TokenServiceFactory::Initialize();

  wake_on_wifi_manager_.reset(new WakeOnWifiManager());
  network_throttling_observer_.reset(
      new NetworkThrottlingObserver(g_browser_process->local_state()));

  arc_service_launcher_ = std::make_unique<arc::ArcServiceLauncher>();
  arc_voice_interaction_controller_client_ =
      std::make_unique<arc::VoiceInteractionControllerClient>();

  chromeos::ResourceReporter::GetInstance()->StartMonitoring(
      task_manager::TaskManagerInterface::GetTaskManager());

  ChromeBrowserMainPartsLinux::PreMainMessageLoopRun();
}
