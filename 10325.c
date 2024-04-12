void LocalDOMWindow::AddedEventListener(
    const AtomicString& event_type,
    RegisteredEventListener& registered_listener) {
  DOMWindow::AddedEventListener(event_type, registered_listener);
  if (GetFrame() && GetFrame()->GetPage())
    GetFrame()->GetPage()->GetEventHandlerRegistry().DidAddEventHandler(
        *this, event_type, registered_listener.Options());

  if (Document* document = this->document())
    document->AddListenerTypeIfNeeded(event_type, *this);

  for (auto& it : event_listener_observers_) {
    it->DidAddEventListener(this, event_type);
  }

  if (event_type == EventTypeNames::unload) {
    UseCounter::Count(document(), WebFeature::kDocumentUnloadRegistered);
    TrackUnloadEventListener(this);
  } else if (event_type == EventTypeNames::beforeunload) {
    UseCounter::Count(document(), WebFeature::kDocumentBeforeUnloadRegistered);
    TrackBeforeUnloadEventListener(this);
    if (GetFrame() && !GetFrame()->IsMainFrame()) {
      UseCounter::Count(document(),
                        WebFeature::kSubFrameBeforeUnloadRegistered);
    }
  } else if (event_type == EventTypeNames::pagehide) {
    UseCounter::Count(document(), WebFeature::kDocumentPageHideRegistered);
  } else if (event_type == EventTypeNames::pageshow) {
    UseCounter::Count(document(), WebFeature::kDocumentPageShowRegistered);
  }
}
