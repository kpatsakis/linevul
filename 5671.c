 void WebPageSerializer::serialize(WebView* view, WebVector<WebPageSerializer::Resource>* resourcesParam)
{
    Vector<SerializedResource> resources;
    PageSerializer serializer(&resources);
    serializer.serialize(toWebViewImpl(view)->page());

    Vector<Resource> result;
    for (Vector<SerializedResource>::const_iterator iter = resources.begin(); iter != resources.end(); ++iter) {
        Resource resource;
        resource.url = iter->url;
        resource.mimeType = iter->mimeType.ascii();
        resource.data = WebCString(iter->data->data(), iter->data->size());
        result.append(resource);
    }

    *resourcesParam = result;
}
