std::unique_ptr<EventMatcher> EventBindings::ParseEventMatcher(
    std::unique_ptr<base::DictionaryValue> filter) {
  return base::WrapUnique(new EventMatcher(
      std::move(filter), context()->GetRenderFrame()->GetRoutingID()));
}
