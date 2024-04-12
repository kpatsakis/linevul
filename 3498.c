void CGaiaCredentialBase::TellOmahaDidRun() {
#if defined(GOOGLE_CHROME_BUILD)
  base::win::RegKey key;
  LONG sts = key.Create(HKEY_CURRENT_USER, kRegUpdaterClientStateAppPath,
                        KEY_SET_VALUE | KEY_WOW64_32KEY);
  if (sts != ERROR_SUCCESS) {
    LOGFN(INFO) << "Unable to open omaha key sts=" << sts;
  } else {
    sts = key.WriteValue(L"dr", L"1");
    if (sts != ERROR_SUCCESS)
      LOGFN(INFO) << "Unable to write omaha dr value sts=" << sts;
  }
#endif  // defined(GOOGLE_CHROME_BUILD)
}
