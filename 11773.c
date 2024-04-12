void Document::enqueueScrollEventForNode(Node* target)
{
    Event* scrollEvent = target->isDocumentNode() ? Event::createBubble(EventTypeNames::scroll) : Event::create(EventTypeNames::scroll);
    scrollEvent->setTarget(target);
    ensureScriptedAnimationController().enqueuePerFrameEvent(scrollEvent);
}
