void Document::setAutofocusElement(Element* element)
{
    if (!element) {
        m_autofocusElement = nullptr;
        return;
    }
    if (m_hasAutofocused)
        return;
    m_hasAutofocused = true;
    ASSERT(!m_autofocusElement);
    m_autofocusElement = element;
    m_taskRunner->postTask(FROM_HERE, AutofocusTask::create());
}
