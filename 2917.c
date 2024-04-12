void ChromeClientImpl::layoutUpdated(Frame* frame) const
{
    m_webView->layoutUpdated(WebFrameImpl::fromFrame(frame));
}
