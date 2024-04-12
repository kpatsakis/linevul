void OutOfProcessPPAPITest::SetUpCommandLine(CommandLine* command_line) {
  PPAPITest::SetUpCommandLine(command_line);

  command_line->AppendSwitch(switches::kPpapiOutOfProcess);
}
