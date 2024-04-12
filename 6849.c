void AppCacheUpdateJob::OnResponseInfoLoaded(
    AppCacheResponseInfo* response_info, int64 response_id) {
  const net::HttpResponseInfo* http_info = response_info ?
      response_info->http_response_info() : NULL;

  if (internal_state_ == FETCH_MANIFEST) {
    if (http_info)
      manifest_fetcher_->set_existing_response_headers(
          http_info->headers.get());
    manifest_fetcher_->Start();
    return;
  }

  LoadingResponses::iterator found = loading_responses_.find(response_id);
  DCHECK(found != loading_responses_.end());
  const GURL& url = found->second;

  if (!http_info) {
    LoadFromNewestCacheFailed(url, NULL);  // no response found
  } else {
    const std::string name = "vary";
    std::string value;
    void* iter = NULL;
    if (!http_info->headers.get() ||
        http_info->headers->RequiresValidation(http_info->request_time,
                                               http_info->response_time,
                                               base::Time::Now()) ||
        http_info->headers->EnumerateHeader(&iter, name, &value)) {
      LoadFromNewestCacheFailed(url, response_info);
    } else {
      DCHECK(group_->newest_complete_cache());
      AppCacheEntry* copy_me = group_->newest_complete_cache()->GetEntry(url);
      DCHECK(copy_me);
      DCHECK(copy_me->response_id() == response_id);

      AppCache::EntryMap::iterator it = url_file_list_.find(url);
      DCHECK(it != url_file_list_.end());
      AppCacheEntry& entry = it->second;
      entry.set_response_id(response_id);
      entry.set_response_size(copy_me->response_size());
      inprogress_cache_->AddOrModifyEntry(url, entry);
      NotifyAllProgress(url);
      ++url_fetches_completed_;
    }
  }
  loading_responses_.erase(found);

  MaybeCompleteUpdate();
}
