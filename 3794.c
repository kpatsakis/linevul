void UrlData::DecreaseLoadersInState(
    UrlDataWithLoadingState::LoadingState state) {
  switch (state) {
    case UrlDataWithLoadingState::LoadingState::kIdle:
      return;
    case UrlDataWithLoadingState::LoadingState::kPreload:
      preloading_--;
      DCHECK_GE(preloading_, 0);
      break;
    case UrlDataWithLoadingState::LoadingState::kHasPlayed:
      playing_--;
      DCHECK_GE(playing_, 0);
      break;
  }
  if (preloading_ == 0 && playing_ == 0)
    url_index_->RemoveLoading(this);
}
