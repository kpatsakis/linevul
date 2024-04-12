void Document::didAssociateFormControlsTimerFired(Timer<Document>* timer)
{
    ASSERT_UNUSED(timer, timer == &m_didAssociateFormControlsTimer);
    if (!frame() || !frame()->page())
        return;

    Vector<RefPtr<Element> > associatedFormControls;
    copyToVector(m_associatedFormControls, associatedFormControls);

    frame()->page()->chrome()->client()->didAssociateFormControls(associatedFormControls);
    m_associatedFormControls.clear();
}
