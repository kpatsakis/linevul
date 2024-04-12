void WorkerFetchContext::PopulateResourceRequest(
    Resource::Type type,
    const ClientHintsPreferences& hints_preferences,
    const FetchParameters::ResourceWidth& resource_width,
    ResourceRequest& out_request) {
  SetFirstPartyCookieAndRequestorOrigin(out_request);
}
