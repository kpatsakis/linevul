void RecordDownloadContentTypeSecurity(
    const GURL& download_url,
    const std::vector<GURL>& url_chain,
    const std::string& mime_type,
    const base::RepeatingCallback<bool(const GURL&)>&
        is_origin_secure_callback) {
  bool is_final_download_secure = is_origin_secure_callback.Run(download_url);
  bool is_redirect_chain_secure = true;
  for (const auto& url : url_chain) {
    if (!is_origin_secure_callback.Run(url)) {
      is_redirect_chain_secure = false;
      break;
    }
  }

  DownloadContent download_content =
      download::DownloadContentFromMimeType(mime_type, false);
  if (is_final_download_secure && is_redirect_chain_secure) {
    UMA_HISTOGRAM_ENUMERATION("Download.Start.ContentType.SecureChain",
                              download_content, DownloadContent::MAX);
  } else {
    UMA_HISTOGRAM_ENUMERATION("Download.Start.ContentType.InsecureChain",
                              download_content, DownloadContent::MAX);
  }
}
