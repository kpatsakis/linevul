AppCacheUpdateJob::AppCacheUpdateJob(AppCacheServiceImpl* service,
                                     AppCacheGroup* group)
    : service_(service),
      manifest_url_(group->manifest_url()),
      group_(group),
      update_type_(UNKNOWN_TYPE),
      internal_state_(FETCH_MANIFEST),
      doing_full_update_check_(false),
      master_entries_completed_(0),
      url_fetches_completed_(0),
      manifest_fetcher_(NULL),
      manifest_has_valid_mime_type_(false),
      stored_state_(UNSTORED),
      storage_(service->storage()),
      weak_factory_(this) {
    service_->AddObserver(this);
}
