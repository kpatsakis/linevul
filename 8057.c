bool TopSitesImpl::IsKnownURL(const GURL& url) {
  return loaded_ && cache_->IsKnownURL(url);
}
