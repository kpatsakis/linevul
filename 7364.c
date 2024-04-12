void ProcessBacktrace(void *const *trace,
                      size_t size,
                      BacktraceOutputHandler* handler) {

#if defined(USE_SYMBOLIZE)
  for (size_t i = 0; i < size; ++i) {
    OutputFrameId(i, handler);
    handler->HandleOutput(" ");
    OutputPointer(trace[i], handler);
    handler->HandleOutput(" ");

    char buf[1024] = { '\0' };

    void* address = static_cast<char*>(trace[i]) - 1;
    if (google::Symbolize(address, buf, sizeof(buf)))
      handler->HandleOutput(buf);
    else
      handler->HandleOutput("<unknown>");

    handler->HandleOutput("\n");
  }
#elif !defined(__UCLIBC__)
  bool printed = false;

  if (in_signal_handler == 0) {
    scoped_ptr<char*, FreeDeleter>
        trace_symbols(backtrace_symbols(trace, size));
    if (trace_symbols.get()) {
      for (size_t i = 0; i < size; ++i) {
        std::string trace_symbol = trace_symbols.get()[i];
        DemangleSymbols(&trace_symbol);
        handler->HandleOutput(trace_symbol.c_str());
        handler->HandleOutput("\n");
      }

      printed = true;
    }
  }

  if (!printed) {
    for (size_t i = 0; i < size; ++i) {
      handler->HandleOutput(" [");
      OutputPointer(trace[i], handler);
      handler->HandleOutput("]\n");
    }
  }
#endif  // defined(USE_SYMBOLIZE)
}
