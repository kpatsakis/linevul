static SiteInstanceImpl* CreateSiteInstance(
    BrowserContext* browser_context,
    RenderProcessHostFactory* factory,
    const GURL& url) {
  SiteInstanceImpl* instance =
      reinterpret_cast<SiteInstanceImpl*>(
          SiteInstance::CreateForURL(browser_context, url));
  instance->set_render_process_host_factory(factory);
  return instance;
}
