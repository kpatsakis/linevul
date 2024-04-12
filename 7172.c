void FrameView::setMediaType(const AtomicString& mediaType)
{
    ASSERT(m_frame->document());
    m_frame->document()->mediaQueryAffectingValueChanged();
    m_mediaType = mediaType;
}
