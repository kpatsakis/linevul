ResourcePtr<RawResource> ResourceFetcher::fetchMainResource(FetchRequest& request, const SubstituteData& substituteData)
{
    if (substituteData.isValid())
        preCacheSubstituteDataForMainResource(request, substituteData);
    return toRawResource(requestResource(Resource::MainResource, request));
}
