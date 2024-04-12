void Document::takeDOMWindowFrom(Document* document)
{
    ASSERT(m_frame);
    ASSERT(!m_domWindow);
    ASSERT(document->domWindow());
    ASSERT(!document->inPageCache());

    m_domWindow = document->m_domWindow.release();
    m_domWindow->didSecureTransitionTo(this);

    ASSERT(m_domWindow->document() == this);
    ASSERT(m_domWindow->frame() == m_frame);
}
