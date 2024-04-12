void Document::didAssociateFormControlsTimerFired(Timer<Document>* timer)
{
    ASSERT_UNUSED(timer, timer == &m_didAssociateFormControlsTimer);
    if (!frame() || !frame()->page())
        return;

    WillBeHeapVector<RefPtrWillBeMember<Element>> associatedFormControls;
    copyToVector(m_associatedFormControls, associatedFormControls);

    frame()->page()->chrome().client().didAssociateFormControls(associatedFormControls, frame());
    m_associatedFormControls.clear();
}
