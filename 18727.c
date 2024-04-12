void SVGStyleElement::DispatchPendingEvent() {
  DispatchEvent(Event::Create(EventTypeNames::error));
}
