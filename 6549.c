void Document::setWindowAttributeEventListener(const AtomicString& eventType, PassRefPtr<EventListener> listener)
{
    LocalDOMWindow* domWindow = this->domWindow();
    if (!domWindow)
        return;
    domWindow->setAttributeEventListener(eventType, listener);
}
