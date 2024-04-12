void ContentSecurityPolicy::LogToConsole(ConsoleMessage* console_message,
                                         LocalFrame* frame) {
  if (frame)
    frame->GetDocument()->AddConsoleMessage(console_message);
  else if (execution_context_)
    execution_context_->AddConsoleMessage(console_message);
  else
    console_messages_.push_back(console_message);
}
