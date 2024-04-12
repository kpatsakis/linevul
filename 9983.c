void Document::enqueueResizeEvent()
{
    RefPtrWillBeRawPtr<Event> event = Event::create(EventTypeNames::resize);
    event->setTarget(domWindow());
    ensureScriptedAnimationController().enqueuePerFrameEvent(event.release());
}
