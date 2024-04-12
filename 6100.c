ResourcePtr<DocumentResource> ResourceFetcher::fetchSVGDocument(FetchRequest& request)
{
    return toDocumentResource(requestResource(Resource::SVGDocument, request));
}
