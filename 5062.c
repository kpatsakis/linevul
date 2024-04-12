void HTMLFrameOwnerElement::DispatchLoad() {
  DispatchScopedEvent(Event::Create(EventTypeNames::load));
}
