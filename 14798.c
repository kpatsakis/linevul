ExternalProtocolHandler::BlockState GetBlockStateWithDelegate(
    const std::string& scheme,
    ExternalProtocolHandler::Delegate* delegate,
    Profile* profile) {
  if (delegate)
    return delegate->GetBlockState(scheme, profile);
  return ExternalProtocolHandler::GetBlockState(scheme, profile);
}
