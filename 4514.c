void Document::didAssociateFormControl(Element* element)
{
    if (!frame() || !frame()->page())
        return;
    m_associatedFormControls.add(element);
    if (!m_didAssociateFormControlsTimer.isActive())
        m_didAssociateFormControlsTimer.startOneShot(0);
}
