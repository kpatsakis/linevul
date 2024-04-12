void Document::setWindowAttributeEventListener(const AtomicString& eventType, PassRefPtr<EventListener> listener, DOMWrapperWorld* isolatedWorld)
{
    DOMWindow* domWindow = this->domWindow();
    if (!domWindow)
        return;
    domWindow->setAttributeEventListener(eventType, listener, isolatedWorld);
}
