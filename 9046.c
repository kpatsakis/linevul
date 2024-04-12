void ChromeContentBrowserClient::HandleServiceRequest(
    const std::string& service_name,
    service_manager::mojom::ServiceRequest request) {
  if (service_name == prefs::mojom::kLocalStateServiceName) {
    if (!g_browser_process || !g_browser_process->pref_service_factory())
      return;

    service_manager::Service::RunAsyncUntilTermination(
        g_browser_process->pref_service_factory()->CreatePrefService(
            std::move(request)));
  }

#if BUILDFLAG(ENABLE_MOJO_MEDIA_IN_BROWSER_PROCESS)
  if (service_name == media::mojom::kMediaServiceName) {
    service_manager::Service::RunAsyncUntilTermination(
        media::CreateMediaService(std::move(request)));
  }
#endif

#if BUILDFLAG(ENABLE_SIMPLE_BROWSER_SERVICE_IN_PROCESS)
  if (base::CommandLine::ForCurrentProcess()->HasSwitch(
          switches::kLaunchInProcessSimpleBrowserSwitch) &&
      service_name == simple_browser::mojom::kServiceName) {
    service_manager::Service::RunAsyncUntilTermination(
        std::make_unique<simple_browser::SimpleBrowserService>(
            std::move(request), simple_browser::SimpleBrowserService::
                                    UIInitializationMode::kUseEnvironmentUI));
  }
#endif

#if defined(OS_CHROMEOS)
  if (service_name == chromeos::secure_channel::mojom::kServiceName) {
    service_manager::Service::RunAsyncUntilTermination(
        std::make_unique<chromeos::secure_channel::SecureChannelService>(
            std::move(request)));
  }

  auto service = ash_service_registry::HandleServiceRequest(service_name,
                                                            std::move(request));
  if (service)
    service_manager::Service::RunAsyncUntilTermination(std::move(service));
#endif
}
