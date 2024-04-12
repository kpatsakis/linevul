std::string RenderThreadImpl::GetLocale() {
  const CommandLine& parsed_command_line = *CommandLine::ForCurrentProcess();
  const std::string& lang =
      parsed_command_line.GetSwitchValueASCII(switches::kLang);
  DCHECK(!lang.empty() ||
      (!parsed_command_line.HasSwitch(switches::kRendererProcess) &&
       !parsed_command_line.HasSwitch(switches::kPluginProcess)));
  return lang;
}
