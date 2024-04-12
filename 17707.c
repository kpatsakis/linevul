void SupervisedUserService::ReportURL(const GURL& url,
                                      SuccessCallback callback) {
  if (url_reporter_)
    url_reporter_->ReportUrl(url, std::move(callback));
  else
    std::move(callback).Run(false);
}
