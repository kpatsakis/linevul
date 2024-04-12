void CaptivePortalDetector::OnURLFetchComplete(const net::URLFetcher* source) {
  DCHECK(CalledOnValidThread());
  DCHECK(FetchingURL());
  DCHECK_EQ(url_fetcher_.get(), source);
  DCHECK(!detection_callback_.is_null());

  Results results;
  GetCaptivePortalResultFromResponse(url_fetcher_.get(), &results);
  DetectionCallback callback = detection_callback_;
  url_fetcher_.reset();
  detection_callback_.Reset();
  callback.Run(results);
}
