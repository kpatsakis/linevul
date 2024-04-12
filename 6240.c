bool DebuggerAttachFunction::RunAsync() {
  std::unique_ptr<Attach::Params> params(Attach::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  CopyDebuggee(&debuggee_, params->target);
  if (!InitAgentHost())
    return false;

  if (!DevToolsAgentHost::IsSupportedProtocolVersion(
          params->required_version)) {
    error_ = ErrorUtils::FormatErrorMessage(
        debugger_api_constants::kProtocolVersionNotSupportedError,
        params->required_version);
    return false;
  }

  if (FindClientHost()) {
    FormatErrorMessage(debugger_api_constants::kAlreadyAttachedError);
    return false;
  }

  auto host = std::make_unique<ExtensionDevToolsClientHost>(
      GetProfile(), agent_host_.get(), extension(), debuggee_);

  if (!host->Attach()) {
    FormatErrorMessage(debugger_api_constants::kRestrictedError);
    return false;
  }

  host.release();  // An attached client host manages its own lifetime.
  SendResponse(true);
  return true;
}
