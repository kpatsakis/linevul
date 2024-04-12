void FrameFetchContext::PopulateResourceRequest(
    Resource::Type type,
    const ClientHintsPreferences& hints_preferences,
    const FetchParameters::ResourceWidth& resource_width,
    ResourceRequest& request) {
  ModifyRequestForCSP(request);
  AddClientHintsIfNecessary(hints_preferences, resource_width, request);
  AddCSPHeaderIfNecessary(type, request);
}
