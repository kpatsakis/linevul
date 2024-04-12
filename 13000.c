void WebKitTestController::OnPrintMessage(const std::string& message) {
  printer_->AddMessageRaw(message);
}
