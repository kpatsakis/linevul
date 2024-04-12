void HTMLMediaElement::CancelPendingEventsAndCallbacks() {
  BLINK_MEDIA_LOG << "cancelPendingEventsAndCallbacks(" << (void*)this << ")";
  async_event_queue_->CancelAllEvents();

  for (HTMLSourceElement* source =
           Traversal<HTMLSourceElement>::FirstChild(*this);
       source; source = Traversal<HTMLSourceElement>::NextSibling(*source))
    source->CancelPendingErrorEvent();
}
