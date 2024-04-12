void InitRenderViewHostForExtensions(RenderViewHost* render_view_host) {
  SiteInstance* site_instance = render_view_host->site_instance();
  const GURL& site = site_instance->site();

  if (!site.SchemeIs(chrome::kExtensionScheme))
    return;

  Profile* profile = site_instance->browsing_instance()->profile();
  ExtensionService* service = profile->GetExtensionService();
  if (!service)
    return;

  ExtensionProcessManager* process_manager =
      profile->GetExtensionProcessManager();
  CHECK(process_manager);

  const Extension* extension = service->GetExtensionByURL(site);
  if (!extension)
    return;

  site_instance->GetProcess()->mark_is_extension_process();

  process_manager->RegisterExtensionSiteInstance(site_instance->id(),
                                                 extension->id());

  RenderProcessHost* process = render_view_host->process();

  if (extension->is_app()) {
    render_view_host->Send(
        new ExtensionMsg_ActivateApplication(extension->id()));
    service->SetInstalledAppForRenderer(process->id(), extension);
  }

  Extension::Type type = extension->GetType();
  if (type == Extension::TYPE_EXTENSION ||
      type == Extension::TYPE_PACKAGED_APP) {
    ChildProcessSecurityPolicy::GetInstance()->GrantScheme(
        process->id(), chrome::kChromeUIScheme);
  }

  if (type == Extension::TYPE_EXTENSION ||
      type == Extension::TYPE_USER_SCRIPT ||
      type == Extension::TYPE_PACKAGED_APP ||
      (type == Extension::TYPE_HOSTED_APP &&
       extension->location() == Extension::COMPONENT)) {
    render_view_host->Send(new ExtensionMsg_ActivateExtension(extension->id()));
    render_view_host->AllowBindings(BindingsPolicy::EXTENSION);
  }
}
