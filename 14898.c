ChromeContentBrowserClient::CreateClientCertStore(
    content::ResourceContext* resource_context) {
  if (!resource_context)
    return nullptr;
  return ProfileIOData::FromResourceContext(resource_context)
      ->CreateClientCertStore();
}
