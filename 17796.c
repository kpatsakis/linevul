void WebPagePrivate::notifyInRegionScrollStopped()
{
    if (m_inRegionScroller->d->isActive())
        m_inRegionScroller->d->reset();
}
