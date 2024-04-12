void ResourceFetcher::EnableIsPreloadedForTest() {
  if (preloaded_urls_for_test_)
    return;
  preloaded_urls_for_test_ = WTF::WrapUnique(new HashSet<String>);

  for (const auto& pair : preloads_) {
    Resource* resource = pair.value;
    preloaded_urls_for_test_->insert(resource->Url().GetString());
  }
}
