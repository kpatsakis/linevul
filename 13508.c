HRESULT UrlmonUrlRequest::StartAsyncDownload() {
  DVLOG(1) << __FUNCTION__ << me() << url();
  HRESULT hr = E_FAIL;
  DCHECK((moniker_ && bind_context_) || (!moniker_ && !bind_context_));

  if (!moniker_.get()) {
    std::wstring wide_url = UTF8ToWide(url());
    hr = CreateURLMonikerEx(NULL, wide_url.c_str(), moniker_.Receive(),
                            URL_MK_UNIFORM);
    if (FAILED(hr)) {
      NOTREACHED() << "CreateURLMonikerEx failed. Error: " << hr;
      return hr;
    }
  }

  if (bind_context_.get() == NULL)  {
    hr = ::CreateAsyncBindCtxEx(NULL, 0, this, NULL,
                                bind_context_.Receive(), 0);
    DCHECK(SUCCEEDED(hr)) << "CreateAsyncBindCtxEx failed. Error: " << hr;
  } else {
    hr = ::RegisterBindStatusCallback(bind_context_, this, NULL, 0);
    DCHECK(SUCCEEDED(hr)) << "RegisterBindStatusCallback failed. Error: " << hr;
  }

  if (SUCCEEDED(hr)) {
    base::win::ScopedComPtr<IStream> stream;

    base::win::ScopedComPtr<IHttpSecurity> self(this);

    base::win::ScopedComPtr<BindContextInfo> info;
    BindContextInfo::FromBindContext(bind_context_, info.Receive());
    DCHECK(info);
    if (info)
      info->set_chrome_request(true);

    hr = moniker_->BindToStorage(bind_context_, NULL, __uuidof(IStream),
                                 reinterpret_cast<void**>(stream.Receive()));
    if (hr == S_OK)
      DCHECK(binding_ != NULL || status_.get_state() == Status::DONE);

    if (FAILED(hr)) {
      DLOG(ERROR) << __FUNCTION__ << me() <<
          base::StringPrintf("IUrlMoniker::BindToStorage failed 0x%08X.", hr);
    }
  }

  DLOG_IF(ERROR, FAILED(hr)) << me() <<
      base::StringPrintf(L"StartAsyncDownload failed: 0x%08X", hr);

  return hr;
}
