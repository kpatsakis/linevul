void OutputPointer(void* pointer, BacktraceOutputHandler* handler) {
  char buf[17] = { '\0' };
  handler->HandleOutput("0x");
  internal::itoa_r(reinterpret_cast<intptr_t>(pointer),
                   buf, sizeof(buf), 16, 12);
  handler->HandleOutput(buf);
}
