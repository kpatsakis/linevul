bool ChromeContentBrowserClientExtensionsPart::DoesSiteRequireDedicatedProcess(
    content::BrowserContext* browser_context,
    const GURL& effective_site_url) {
  const Extension* extension = ExtensionRegistry::Get(browser_context)
                                   ->enabled_extensions()
                                   .GetExtensionOrAppByURL(effective_site_url);
  if (!extension)
    return false;

  if (extension->id() == kWebStoreAppId)
    return true;

  if (extension->is_hosted_app())
    return false;

  return true;
}
