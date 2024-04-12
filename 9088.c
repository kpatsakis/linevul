bool ChromeContentBrowserClient::ShouldTerminateOnServiceQuit(
    const service_manager::Identity& id) {
#if defined(OS_CHROMEOS)
  return ash_service_registry::ShouldTerminateOnServiceQuit(id.name());
#endif
  return false;
}
