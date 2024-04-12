void AppCacheUpdateJob::CancelAllUrlFetches() {
  for (PendingUrlFetches::iterator it = pending_url_fetches_.begin();
       it != pending_url_fetches_.end(); ++it) {
    delete it->second;
  }

  url_fetches_completed_ +=
      pending_url_fetches_.size() + urls_to_fetch_.size();
  pending_url_fetches_.clear();
  urls_to_fetch_.clear();
}
