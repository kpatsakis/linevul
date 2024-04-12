ExtensionRegistry* ExtensionRegistry::Get(content::BrowserContext* context) {
  return ExtensionRegistryFactory::GetForBrowserContext(context);
}
