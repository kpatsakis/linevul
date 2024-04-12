void ChromeContentBrowserClient::AdjustUtilityServiceProcessCommandLine(
    const service_manager::Identity& identity,
    base::CommandLine* command_line) {
#if defined(OS_CHROMEOS)
  bool copy_switches = false;
  if (identity.name() == ash::mojom::kServiceName) {
    copy_switches = true;
    command_line->AppendSwitch(switches::kMessageLoopTypeUi);
  }
  if (ash_service_registry::IsAshRelatedServiceName(identity.name())) {
    copy_switches = true;
    command_line->AppendSwitchASCII(switches::kMashServiceName,
                                    identity.name());
  }
  if (identity.name() == viz::mojom::kVizServiceName)
    content::GpuDataManager::GetInstance()->AppendGpuCommandLine(command_line);
  if (copy_switches) {
    for (const auto& sw : base::CommandLine::ForCurrentProcess()->GetSwitches())
      command_line->AppendSwitchNative(sw.first, sw.second);
  }
#endif

#if defined(OS_MACOSX)
  if (identity.name() == video_capture::mojom::kServiceName ||
      identity.name() == audio::mojom::kServiceName)
    command_line->AppendSwitch(switches::kMessageLoopTypeUi);
#endif
}
