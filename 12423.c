BrandcodeConfigFetcher::BrandcodeConfigFetcher(
    network::mojom::URLLoaderFactory* url_loader_factory,
    const FetchCallback& callback,
    const GURL& url,
    const std::string& brandcode)
    : fetch_callback_(callback) {
  DCHECK(!brandcode.empty());
  net::NetworkTrafficAnnotationTag traffic_annotation =
      net::DefineNetworkTrafficAnnotation("brandcode_config", R"(
        semantics {
          sender: "Brandcode Configuration Fetcher"
          description:
            "Chrome installation can be non-organic. That means that Chrome "
            "is distributed by partners and it has a brand code associated "
            "with that partner. For the settings reset operation, Chrome needs "
            "to know the default settings which are partner specific."
          trigger: "'Reset Settings' invocation from Chrome settings."
          data: "Brandcode."
          destination: GOOGLE_OWNED_SERVICE
        }
        policy {
          cookies_allowed: NO
          setting:
            "This feature cannot be disabled and is only invoked by user "
            "request."
          policy_exception_justification:
            "Not implemented, considered not useful as enterprises don't need "
            "to install Chrome in a non-organic fashion."
        })");
  auto resource_request = std::make_unique<network::ResourceRequest>();
  resource_request->url = url;
  resource_request->load_flags = net::LOAD_DO_NOT_SEND_COOKIES |
                                 net::LOAD_DO_NOT_SAVE_COOKIES |
                                 net::LOAD_DISABLE_CACHE;
  resource_request->method = "POST";
  resource_request->headers.SetHeader("Accept", "text/xml");
  simple_url_loader_ = network::SimpleURLLoader::Create(
      std::move(resource_request), traffic_annotation);
  simple_url_loader_->AttachStringForUpload(GetUploadData(brandcode),
                                            "text/xml");
  simple_url_loader_->DownloadToStringOfUnboundedSizeUntilCrashAndDie(
      url_loader_factory,
      base::BindOnce(&BrandcodeConfigFetcher::OnSimpleLoaderComplete,
                     base::Unretained(this)));
  download_timer_.Start(FROM_HERE,
                        base::TimeDelta::FromSeconds(kDownloadTimeoutSec),
                        this,
                        &BrandcodeConfigFetcher::OnDownloadTimeout);
}
