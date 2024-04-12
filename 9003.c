void WebPage::setDocumentScrollPosition(const Platform::IntPoint& documentScrollPosition)
{
    WebCore::IntPoint scrollPosition = documentScrollPosition;
    if (scrollPosition == d->scrollPosition())
        return;

    if (currentTime() - d->m_lastUserEventTimestamp < manualScrollInterval)
        d->m_userPerformedManualScroll = true;

    d->m_backingStoreClient->setIsClientGeneratedScroll(true);

    bool constrainsScrollingToContentEdge = d->m_mainFrame->view()->constrainsScrollingToContentEdge();
    d->m_mainFrame->view()->setConstrainsScrollingToContentEdge(false);
    d->setScrollPosition(scrollPosition);
    d->m_mainFrame->view()->setConstrainsScrollingToContentEdge(constrainsScrollingToContentEdge);

    d->m_backingStoreClient->setIsClientGeneratedScroll(false);
}
