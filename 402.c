void GpuProcessHost::DidDestroyOffscreenContext(const GURL& url) {
  auto candidate = urls_with_live_offscreen_contexts_.find(url);
  if (candidate != urls_with_live_offscreen_contexts_.end()) {
    urls_with_live_offscreen_contexts_.erase(candidate);
  }
}
