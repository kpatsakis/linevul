void WebPageProxy::didStartProgress()
{
    m_estimatedProgress = initialProgressValue;

    m_loaderClient.didStartProgress(this);
}
