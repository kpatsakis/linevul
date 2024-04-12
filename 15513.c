void WebPage::removeCompositingThreadOverlay(WebOverlay* overlay)
{
#if USE(ACCELERATED_COMPOSITING)
    ASSERT(Platform::userInterfaceThreadMessageClient()->isCurrentThread());
    if (d->compositor())
        d->compositor()->removeOverlay(overlay->d->layerCompositingThread());
    overlay->d->clear();
    overlay->d->setPage(0);
#endif
}
