void DebuggerSendCommandFunction::SendDetachedError() {
  error_ = debugger_api_constants::kDetachedWhileHandlingError;
  SendResponse(false);
}
