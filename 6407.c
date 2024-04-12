ResourcePtr<RawResource> ResourceFetcher::fetchRawResource(FetchRequest& request)
{
    return toRawResource(requestResource(Resource::Raw, request));
}
