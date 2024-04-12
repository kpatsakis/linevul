void LocalSiteCharacteristicsWebContentsObserver::OnLoadingStateChange(
    content::WebContents* contents,
    LoadingState old_loading_state,
    LoadingState new_loading_state) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  if (web_contents() != contents)
    return;

  if (!writer_)
    return;

  if (new_loading_state == LoadingState::LOADED) {
    writer_->NotifySiteLoaded();
  } else if (old_loading_state == LoadingState::LOADED) {
    writer_->NotifySiteUnloaded();
  }
}
