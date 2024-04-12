void InstallablePaymentAppCrawler::WarnIfPossible(const std::string& message) {
  if (web_contents()) {
    web_contents()->GetMainFrame()->AddMessageToConsole(
        content::ConsoleMessageLevel::CONSOLE_MESSAGE_LEVEL_WARNING, message);
  } else {
    LOG(WARNING) << message;
  }
}
