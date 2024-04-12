const Extension* ExtensionWebContentsObserver::GetExtensionFromFrame(
    content::RenderFrameHost* render_frame_host) const {
  return ExtensionRegistry::Get(
             render_frame_host->GetProcess()->GetBrowserContext())
      ->enabled_extensions()
      .GetByID(GetExtensionIdFromFrame(render_frame_host));
}
