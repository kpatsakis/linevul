void ChromeRenderProcessObserver::OnClearCache(bool on_navigation) {
  if (on_navigation) {
    clear_cache_pending_ = true;
  } else {
    WebCache::clear();
  }
}
