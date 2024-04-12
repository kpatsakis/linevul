GURL ChromeContentBrowserClient::GetEffectiveURL(Profile* profile,
                                                 const GURL& url) {
  if (!profile || !profile->GetExtensionService())
    return url;

  const Extension* extension =
      profile->GetExtensionService()->GetExtensionByWebExtent(url);
  if (!extension)
    return url;

  return extension->GetResourceURL(url.path());
}
