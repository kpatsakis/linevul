const GURL& DownloadItemImpl::GetURL() const {
  return url_chain_.empty() ?
             GURL::EmptyGURL() : url_chain_.back();
}
