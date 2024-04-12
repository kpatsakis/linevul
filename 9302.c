ResourceRequest FrameLoader::resourceRequestForReload(FrameLoadType frameLoadType,
    const KURL& overrideURL, ClientRedirectPolicy clientRedirectPolicy)
{
    ASSERT(frameLoadType == FrameLoadTypeReload || frameLoadType == FrameLoadTypeReloadMainResource || frameLoadType == FrameLoadTypeReloadBypassingCache);
    WebCachePolicy cachePolicy = frameLoadType == FrameLoadTypeReloadBypassingCache ? WebCachePolicy::BypassingCache : WebCachePolicy::ValidatingCacheData;
    if (!m_currentItem)
        return ResourceRequest();
    ResourceRequest request = resourceRequestFromHistoryItem(m_currentItem.get(), cachePolicy);

    if (clientRedirectPolicy == ClientRedirectPolicy::ClientRedirect) {
        request.setHTTPReferrer(Referrer(m_frame->document()->outgoingReferrer(),
            m_frame->document()->getReferrerPolicy()));
    }

    if (!overrideURL.isEmpty()) {
        request.setURL(overrideURL);
        request.clearHTTPReferrer();
    }
    request.setSkipServiceWorker(frameLoadType == FrameLoadTypeReloadBypassingCache);
    return request;
}
