void ImageResource::ReloadIfLoFiOrPlaceholderImage(
    ResourceFetcher* fetcher,
    ReloadLoFiOrPlaceholderPolicy policy) {
  if (policy == kReloadIfNeeded && !ShouldReloadBrokenPlaceholder())
    return;

  DCHECK(!IsLoaded() ||
         HasServerLoFiResponseHeaders(GetResponse()) ==
             static_cast<bool>(GetResourceRequest().GetPreviewsState() &
                               WebURLRequest::kServerLoFiOn));

  if (placeholder_option_ == PlaceholderOption::kDoNotReloadPlaceholder &&
      !(GetResourceRequest().GetPreviewsState() & WebURLRequest::kServerLoFiOn))
    return;

  DCHECK(!is_scheduling_reload_);
  is_scheduling_reload_ = true;

  SetCachePolicyBypassingCache();

  WebURLRequest::PreviewsState previews_state_for_reload =
      WebURLRequest::kPreviewsNoTransform;
  WebURLRequest::PreviewsState old_previews_state =
      GetResourceRequest().GetPreviewsState();

  if (policy == kReloadIfNeeded && (GetResourceRequest().GetPreviewsState() &
                                    WebURLRequest::kClientLoFiOn)) {
    previews_state_for_reload |= WebURLRequest::kClientLoFiAutoReload;
  }
  SetPreviewsState(previews_state_for_reload);

  if (placeholder_option_ != PlaceholderOption::kDoNotReloadPlaceholder)
    ClearRangeRequestHeader();

  if (old_previews_state & WebURLRequest::kClientLoFiOn &&
      policy != kReloadAlways) {
    placeholder_option_ = PlaceholderOption::kShowAndDoNotReloadPlaceholder;
  } else {
    placeholder_option_ = PlaceholderOption::kDoNotReloadPlaceholder;
  }

  if (IsLoading()) {
    Loader()->Cancel();
  } else {
    ClearData();
    SetEncodedSize(0);
    UpdateImage(nullptr, ImageResourceContent::kClearImageAndNotifyObservers,
                false);
  }

  SetStatus(ResourceStatus::kNotStarted);

  DCHECK(is_scheduling_reload_);
  is_scheduling_reload_ = false;

  fetcher->StartLoad(this);
}
