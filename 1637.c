void LocalSiteCharacteristicsWebContentsObserver::DidUpdateFaviconURL(
    const std::vector<content::FaviconURL>& candidates) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  if (!first_time_favicon_set_) {
    first_time_favicon_set_ = true;
    return;
  }

  MaybeNotifyBackgroundFeatureUsage(
      &SiteCharacteristicsDataWriter::NotifyUpdatesFaviconInBackground);
}
