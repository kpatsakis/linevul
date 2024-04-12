FrameView* Document::view() const
{
    return m_frame ? m_frame->view() : 0;
}
