void BlinkTestRunner::SimulateWebNotificationClick(const std::string& title) {
  Send(new LayoutTestHostMsg_SimulateWebNotificationClick(routing_id(), title));
}
