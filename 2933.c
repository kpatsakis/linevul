const ResourceLoaderOptions& ResourceFetcher::defaultResourceOptions()
{
    DEFINE_STATIC_LOCAL(ResourceLoaderOptions, options, (SniffContent, BufferData, AllowStoredCredentials, ClientRequestedCredentials, CheckContentSecurityPolicy, DocumentContext));
    return options;
}
