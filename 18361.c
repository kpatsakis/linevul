void ChromeBrowserMainPartsChromeos::PreMainMessageLoopStart() {
  if (!parameters().ui_task) {
    bool use_stub = parameters().command_line.HasSwitch(switches::kStubCros);
    chromeos::CrosLibrary::Initialize(use_stub);
  }
  net::NetworkChangeNotifier::SetFactory(
      new chromeos::CrosNetworkChangeNotifierFactory());

  ChromeBrowserMainPartsLinux::PreMainMessageLoopStart();
}
