blink::WebRelatedAppsFetcher* RenderFrameImpl::GetRelatedAppsFetcher() {
  if (!related_apps_fetcher_)
    related_apps_fetcher_.reset(new RelatedAppsFetcher(&GetManifestManager()));

  return related_apps_fetcher_.get();
}
