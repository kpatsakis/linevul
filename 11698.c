HRESULT CreateCredential(ICredentialProviderCredential** credential) {
  return CComCreator<CComObject<CTestCredentialForBase>>::CreateInstance(
      nullptr, IID_ICredentialProviderCredential,
      reinterpret_cast<void**>(credential));
}
