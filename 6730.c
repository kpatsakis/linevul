bool CredentialManagerImpl::IsZeroClickAllowed() const {
  return *auto_signin_enabled_ && !client_->IsIncognito();
}
