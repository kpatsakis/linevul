STDMETHODIMP UrlmonUrlRequest::OnResponse(DWORD dwResponseCode,
    const wchar_t* response_headers, const wchar_t* request_headers,
    wchar_t** additional_headers) {
  DCHECK_EQ(thread_, base::PlatformThread::CurrentId());
  DVLOG(1) << __FUNCTION__ << me() << "headers: \n" << response_headers;

  if (!delegate_) {
    DLOG(WARNING) << "Invalid delegate";
    return S_OK;
  }

  std::string raw_headers = WideToUTF8(response_headers);

  delegate_->AddPrivacyDataForUrl(url(), "", 0);


  if (enable_frame_busting_) {
    if (http_utils::HasFrameBustingHeader(raw_headers)) {
      DLOG(ERROR) << "X-Frame-Options header other than ALLOWALL " <<
          "detected, navigation canceled";
      return E_FAIL;
    }
  }

  DVLOG(1) << __FUNCTION__ << me() << "Calling OnResponseStarted";

  headers_received_ = true;
  DCHECK_NE(id(), -1);
  delegate_->OnResponseStarted(id(),
                    "",                   // mime_type
                    raw_headers.c_str(),  // headers
                    0,                    // size
                    base::Time(),         // last_modified
                    status_.get_redirection().utf8_url,
                    status_.get_redirection().http_code,
                    socket_address_);
  return S_OK;
}
