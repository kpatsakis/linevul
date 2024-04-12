DownloadResourceHandler::DownloadResourceHandler(
    net::URLRequest* request,
    const std::string& request_origin,
    download::DownloadSource download_source,
    bool follow_cross_origin_redirects)
    : ResourceHandler(request),
      tab_info_(new DownloadTabInfo()),
      follow_cross_origin_redirects_(follow_cross_origin_redirects),
      first_origin_(url::Origin::Create(request->url())),
      core_(request, this, false, request_origin, download_source) {
  const ResourceRequestInfoImpl* request_info = GetRequestInfo();
  base::PostTaskWithTraits(
      FROM_HERE, {BrowserThread::UI},
      base::BindOnce(
          &InitializeDownloadTabInfoOnUIThread,
          DownloadRequestHandle(AsWeakPtr(),
                                request_info->GetWebContentsGetterForRequest()),
          tab_info_.get()));
}
