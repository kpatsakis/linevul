HRESULT CGaiaCredentialBase::GetBitmapValueImpl(DWORD field_id,
                                                HBITMAP* phbmp) {
  HRESULT hr = E_INVALIDARG;
  switch (field_id) {
    case FID_PROVIDER_LOGO:
      *phbmp = ::LoadBitmap(CURRENT_MODULE(),
                            MAKEINTRESOURCE(IDB_GOOGLE_LOGO_SMALL));
      if (*phbmp)
        hr = S_OK;
      break;
    default:
      break;
  }

  return hr;
}
