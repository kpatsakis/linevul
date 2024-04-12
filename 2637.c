MediaControlOverlayEnclosureElement::preDispatchEventHandler(Event* event) {
  if (event && (event->type() == EventTypeNames::click ||
                event->type() == EventTypeNames::touchstart))
    mediaControls().showOverlayCastButtonIfNeeded();
  return MediaControlDivElement::preDispatchEventHandler(event);
}
