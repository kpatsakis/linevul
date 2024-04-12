void UpdateProcessTypeToGpuBroker() {
  base::CommandLine::StringVector exec =
      base::CommandLine::ForCurrentProcess()->GetArgs();
  base::CommandLine::Reset();
  base::CommandLine::Init(0, NULL);
  base::CommandLine::ForCurrentProcess()->InitFromArgv(exec);
  base::CommandLine::ForCurrentProcess()->AppendSwitchASCII(
      switches::kProcessType, "gpu-broker");

  SetProcessTitleFromCommandLine(NULL);
}
