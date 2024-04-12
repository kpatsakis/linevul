  void AppendContentBrowserClientSwitches() {
    client_.AppendExtraCommandLineSwitches(&command_line_, kFakeChildProcessId);
  }
