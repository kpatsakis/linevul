void WebPagePrivate::contentsSizeChanged(const IntSize& contentsSize)
{
    if (m_previousContentsSize == contentsSize)
        return;

    m_contentsSizeChanged = true;

#if DEBUG_WEBPAGE_LOAD
    Platform::logAlways(Platform::LogLevelInfo, "WebPagePrivate::contentsSizeChanged %s", Platform::IntSize(contentsSize).toString().c_str());
#endif
}
