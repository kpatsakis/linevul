void RegisterComponentsForUpdate(const CommandLine& command_line) {
  ComponentUpdateService* cus = g_browser_process->component_updater();
  if (!cus)
    return;
  RegisterRecoveryComponent(cus, g_browser_process->local_state());
  RegisterPepperFlashComponent(cus);
  RegisterNPAPIFlashComponent(cus);
  RegisterSwiftShaderComponent(cus);

  if (command_line.HasSwitch(switches::kEnableCRLSets))
    g_browser_process->crl_set_fetcher()->StartInitialLoad(cus);

  if (command_line.HasSwitch(switches::kEnablePnacl)) {
    RegisterPnaclComponent(cus);
  }

  cus->Start();
}
