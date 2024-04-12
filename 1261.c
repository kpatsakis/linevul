void ResourcePrefetchPredictor::RecordPageRequestSummary(
    std::unique_ptr<PageRequestSummary> summary) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  if (initialization_state_ == NOT_INITIALIZED) {
    StartInitialization();
    return;
  } else if (initialization_state_ == INITIALIZING) {
    return;
  } else if (initialization_state_ != INITIALIZED) {
    NOTREACHED() << "Unexpected initialization_state_: "
                 << initialization_state_;
    return;
  }

  LearnRedirect(summary->initial_url.host(), summary->main_frame_url,
                host_redirect_data_.get());
  LearnOrigins(summary->main_frame_url.host(),
               summary->main_frame_url.GetOrigin(), summary->origins);

  if (observer_)
    observer_->OnNavigationLearned(*summary);
}
