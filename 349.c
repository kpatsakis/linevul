void HttpBridge::OnURLFetchComplete(const URLFetcher *source,
                                    const GURL &url,
                                    const net::URLRequestStatus &status,
                                    int response_code,
                                    const net::ResponseCookies &cookies,
                                    const std::string &data) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::IO));
  base::AutoLock lock(fetch_state_lock_);
  if (fetch_state_.aborted)
    return;

  fetch_state_.request_completed = true;
  fetch_state_.request_succeeded =
      (net::URLRequestStatus::SUCCESS == status.status());
  fetch_state_.http_response_code = response_code;
  fetch_state_.os_error_code = status.os_error();

  fetch_state_.response_content = data;
  fetch_state_.response_headers = source->response_headers();

  MessageLoop::current()->DeleteSoon(FROM_HERE, fetch_state_.url_poster);
  fetch_state_.url_poster = NULL;

  http_post_completed_.Signal();
}
