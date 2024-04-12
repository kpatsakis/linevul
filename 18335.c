void RenderFrameHostManager::ActiveFrameCountIsZero(
    SiteInstanceImpl* site_instance) {
  RenderFrameProxyHost* proxy = GetRenderFrameProxyHost(site_instance);
  CHECK(proxy);

  DeleteRenderFrameProxyHost(site_instance);
}
