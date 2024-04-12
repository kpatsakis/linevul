void AppCacheGroup::AddNewlyDeletableResponseIds(
    std::vector<int64_t>* response_ids) {
  if (is_being_deleted() || (!is_obsolete() && old_caches_.empty())) {
    storage_->DeleteResponses(manifest_url_, *response_ids);
    response_ids->clear();
    return;
  }

  if (newly_deletable_response_ids_.empty()) {
    newly_deletable_response_ids_.swap(*response_ids);
    return;
  }
  newly_deletable_response_ids_.insert(
      newly_deletable_response_ids_.end(),
      response_ids->begin(), response_ids->end());
  response_ids->clear();
}
