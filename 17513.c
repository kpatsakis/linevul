void UrlmonUrlRequestManager::SetInfoForUrl(const std::wstring& url,
                                            IMoniker* moniker, LPBC bind_ctx) {
  CComObject<UrlmonUrlRequest>* new_request = NULL;
  CComObject<UrlmonUrlRequest>::CreateInstance(&new_request);
  if (new_request) {
    GURL start_url(url);
    DCHECK(start_url.is_valid());
    DCHECK(pending_request_ == NULL);

    base::win::ScopedComPtr<BindContextInfo> info;
    BindContextInfo::FromBindContext(bind_ctx, info.Receive());
    DCHECK(info);
    IStream* cache = info ? info->cache() : NULL;
    pending_request_ = new_request;
    pending_request_->InitPending(start_url, moniker, bind_ctx,
                                  enable_frame_busting_, privileged_mode_,
                                  notification_window_, cache);
    bool is_started = pending_request_->Start();
    DCHECK(is_started);
  }
}
