void ImageInputType::handleDOMActivateEvent(Event* event)
{
    RefPtrWillBeRawPtr<HTMLInputElement> element(this->element());
    if (element->isDisabledFormControl() || !element->form())
        return;
    element->setActivatedSubmit(true);
    m_clickLocation = extractClickLocation(event);
    element->form()->prepareForSubmission(event); // Event handlers can run.
    element->setActivatedSubmit(false);
    event->setDefaultHandled();
}
