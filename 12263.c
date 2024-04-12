HRESULT CGaiaCredentialBase::CreateGaiaLogonToken(
    base::win::ScopedHandle* token,
    PSID* sid) {
  DCHECK(token);
  DCHECK(sid);

  auto policy = ScopedLsaPolicy::Create(POLICY_ALL_ACCESS);
  if (!policy) {
    LOGFN(ERROR) << "LsaOpenPolicy failed";
    return E_UNEXPECTED;
  }

  wchar_t gaia_username[kWindowsUsernameBufferLength];
  HRESULT hr = policy->RetrievePrivateData(kLsaKeyGaiaUsername, gaia_username,
                                           base::size(gaia_username));

  if (FAILED(hr)) {
    LOGFN(ERROR) << "Retrieve gaia username hr=" << putHR(hr);
    return hr;
  }
  wchar_t password[32];
  hr = policy->RetrievePrivateData(kLsaKeyGaiaPassword, password,
                                   base::size(password));
  if (FAILED(hr)) {
    LOGFN(ERROR) << "Retrieve password for gaia user '" << gaia_username
                 << "' hr=" << putHR(hr);
    return hr;
  }

  base::string16 local_domain = OSUserManager::GetLocalDomain();
  hr = OSUserManager::Get()->CreateLogonToken(local_domain.c_str(),
                                              gaia_username, password,
                                              /*interactive=*/false, token);
  if (FAILED(hr)) {
    LOGFN(ERROR) << "CreateLogonToken hr=" << putHR(hr);
    return hr;
  }

  hr = OSProcessManager::Get()->GetTokenLogonSID(*token, sid);
  if (FAILED(hr)) {
    LOGFN(ERROR) << "GetTokenLogonSID hr=" << putHR(hr);
    token->Close();
    return hr;
  }

  wchar_t* sid_string;
  if (::ConvertSidToStringSid(*sid, &sid_string)) {
    LOGFN(INFO) << "logon-sid=" << sid_string;
    LocalFree(sid_string);
  } else {
    LOGFN(ERROR) << "logon-sid=<can't get string>";
  }

  return S_OK;
}
