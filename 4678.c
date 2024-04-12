void SafeBrowsingBlockingPage::ShowBlockingPage(
    SafeBrowsingService* sb_service,
    const SafeBrowsingService::UnsafeResource& unsafe_resource) {
  TabContents* tab_contents = tab_util::GetTabContentsByID(
      unsafe_resource.render_process_host_id, unsafe_resource.render_view_id);

  InterstitialPage* interstitial =
      InterstitialPage::GetInterstitialPage(tab_contents);
  if (interstitial && !unsafe_resource.is_subresource) {
    interstitial->DontProceed();
    interstitial = NULL;
  }

  if (!interstitial) {
    std::vector<SafeBrowsingService::UnsafeResource> resources;
    resources.push_back(unsafe_resource);
    if (!factory_)
      factory_ = g_safe_browsing_blocking_page_factory_impl.Pointer();
    SafeBrowsingBlockingPage* blocking_page =
        factory_->CreateSafeBrowsingPage(sb_service, tab_contents, resources);
    blocking_page->Show();
    return;
  }

  UnsafeResourceMap* unsafe_resource_map = GetUnsafeResourcesMap();
  (*unsafe_resource_map)[tab_contents].push_back(unsafe_resource);
}
