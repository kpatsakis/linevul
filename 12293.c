void AppCacheUpdateJob::HandleManifestRefetchCompleted(
    URLFetcher* fetcher) {
  DCHECK(internal_state_ == REFETCH_MANIFEST);
  DCHECK(manifest_fetcher_ == fetcher);
  manifest_fetcher_ = NULL;

  net::URLRequest* request = fetcher->request();
  int response_code = request->status().is_success()
      ? request->GetResponseCode() : -1;
  if (response_code == 304 || manifest_data_ == fetcher->manifest_data()) {
    AppCacheEntry* entry = inprogress_cache_->GetEntry(manifest_url_);
    if (entry) {
      entry->add_types(AppCacheEntry::MANIFEST);
      StoreGroupAndCache();
    } else {
      manifest_response_writer_.reset(CreateResponseWriter());
      scoped_refptr<HttpResponseInfoIOBuffer> io_buffer(
          new HttpResponseInfoIOBuffer(manifest_response_info_.release()));
      manifest_response_writer_->WriteInfo(
          io_buffer.get(),
          base::Bind(&AppCacheUpdateJob::OnManifestInfoWriteComplete,
                     base::Unretained(this)));
    }
  } else {
    VLOG(1) << "Request status: " << request->status().status()
            << " error: " << request->status().error()
            << " response code: " << response_code;
    ScheduleUpdateRetry(kRerunDelayMs);
    if (response_code == 200) {
      HandleCacheFailure(AppCacheErrorDetails("Manifest changed during update",
                                      APPCACHE_CHANGED_ERROR,
                                      GURL(),
                                      0,
                                      false /*is_cross_origin*/),
                         MANIFEST_ERROR,
                         GURL());
    } else {
      const char* kFormatString = "Manifest re-fetch failed (%d) %s";
      std::string message = FormatUrlErrorMessage(
          kFormatString, manifest_url_, fetcher->result(), response_code);
      HandleCacheFailure(AppCacheErrorDetails(message,
                                      APPCACHE_MANIFEST_ERROR,
                                      GURL(),
                                      response_code,
                                      false /*is_cross_origin*/),
                         fetcher->result(),
                         GURL());
    }
  }
}
