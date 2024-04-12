void HTMLAnchorElement::defaultEventHandler(Event* event)
{
    if (isLink()) {
        if (focused() && isEnterKeyKeydownEvent(event) && isLiveLink()) {
            event->setDefaultHandled();
            dispatchSimulatedClick(event);
            return;
        }

        if (isLinkClick(event) && isLiveLink()) {
            handleClick(event);
            return;
        }
    }

    HTMLElement::defaultEventHandler(event);
}
