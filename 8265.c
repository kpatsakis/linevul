void HTMLLinkElement::DidSendDOMContentLoadedForLinkPrerender() {
  DispatchEvent(
      *Event::Create(EventTypeNames::webkitprerenderdomcontentloaded));
}
