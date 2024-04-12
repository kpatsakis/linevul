bool WebFrame::isFrameSet() const
{
    if (!m_coreFrame)
        return false;

    Document* document = m_coreFrame->document();
    if (!document)
        return false;
    return document->isFrameSet();
}
