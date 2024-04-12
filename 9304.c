void BlinkTestRunner::PrintMessage(const std::string& message) {
  Send(new ShellViewHostMsg_PrintMessage(routing_id(), message));
}
