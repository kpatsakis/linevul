void InspectorResourceAgent::replayXHR(ErrorString*, const String& requestId)
{
    String actualRequestId = requestId;

    XHRReplayData* xhrReplayData = m_resourcesData->xhrReplayData(requestId);
    if (!xhrReplayData)
        return;

    ExecutionContext* executionContext = xhrReplayData->executionContext();
    if (!executionContext) {
        m_resourcesData->setXHRReplayData(requestId, 0);
        return;
    }

    RefPtrWillBeRawPtr<XMLHttpRequest> xhr = XMLHttpRequest::create(executionContext);

    Resource* cachedResource = memoryCache()->resourceForURL(xhrReplayData->url());
    if (cachedResource)
        memoryCache()->remove(cachedResource);

    xhr->open(xhrReplayData->method(), xhrReplayData->url(), xhrReplayData->async(), IGNORE_EXCEPTION);
    HTTPHeaderMap::const_iterator end = xhrReplayData->headers().end();
    for (HTTPHeaderMap::const_iterator it = xhrReplayData->headers().begin(); it!= end; ++it)
        xhr->setRequestHeader(it->key, it->value, IGNORE_EXCEPTION);
    xhr->sendForInspectorXHRReplay(xhrReplayData->formData(), IGNORE_EXCEPTION);
}
