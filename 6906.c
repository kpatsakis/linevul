void ChromeClientImpl::print(Frame* frame)
{
    if (m_webView->client())
        m_webView->client()->printPage(WebFrameImpl::fromFrame(frame));
}
