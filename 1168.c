void DocumentLoader::stopLoading()
{
    RefPtr<Frame> protectFrame(m_frame);
    RefPtr<DocumentLoader> protectLoader(this);

    bool loading = isLoading();
    
    if (m_committed) {
        Document* doc = m_frame->document();
        
        if (loading || doc->parsing())
            m_frame->loader()->stopLoading(UnloadEventPolicyNone);
    }

    cancelAll(m_multipartSubresourceLoaders);

    m_applicationCacheHost->stopLoadingInFrame(m_frame);
    
#if ENABLE(WEB_ARCHIVE) || ENABLE(MHTML)
    clearArchiveResources();
#endif

    if (!loading) {
        ASSERT(!isLoading());
        return;
    }

    if (m_isStopping)
        return;

    m_isStopping = true;

    FrameLoader* frameLoader = DocumentLoader::frameLoader();
    
    if (isLoadingMainResource())
        cancelMainResourceLoad(frameLoader->cancelledError(m_request));
    else if (!m_subresourceLoaders.isEmpty())
        setMainDocumentError(frameLoader->cancelledError(m_request));
    else
        mainReceivedError(frameLoader->cancelledError(m_request));
    
    stopLoadingSubresources();
    stopLoadingPlugIns();
    
    m_isStopping = false;
}
