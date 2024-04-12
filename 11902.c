void Scrollbar::offsetDidChange()
{
    ASSERT(m_scrollableArea);

    float position = static_cast<float>(m_scrollableArea->scrollPosition(this));
    if (position == m_currentPos)
        return;

    int oldThumbPosition = theme()->thumbPosition(this);
    m_currentPos = position;
    updateThumbPosition();
    if (m_pressedPart == ThumbPart)
        setPressedPos(m_pressedPos + theme()->thumbPosition(this) - oldThumbPosition);    
}
