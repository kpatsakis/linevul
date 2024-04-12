static void DumpStackTraceSignalHandler(int signal) {
  base::debug::StackTrace().PrintBacktrace();
  _exit(128 + signal);
}
