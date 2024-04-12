STDMETHODIMP UrlmonUrlRequest::GetWindow(const GUID& guid_reason,
                                         HWND* parent_window) {
  if (!parent_window)
    return E_INVALIDARG;

#ifndef NDEBUG
  wchar_t guid[40] = {0};
  ::StringFromGUID2(guid_reason, guid, arraysize(guid));
  const wchar_t* str = guid;
  if (guid_reason == IID_IAuthenticate)
    str = L"IAuthenticate";
  else if (guid_reason == IID_IHttpSecurity)
    str = L"IHttpSecurity";
  else if (guid_reason == IID_IWindowForBindingUI)
    str = L"IWindowForBindingUI";
  DVLOG(1) << __FUNCTION__ << me() << "GetWindow: " << str;
#endif
  DLOG_IF(WARNING, !::IsWindow(parent_window_))
      << "UrlmonUrlRequest::GetWindow - no window!";
  *parent_window = parent_window_;
  return S_OK;
}
