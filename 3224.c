void EventBindings::MatchAgainstEventFilter(
    const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();
  typedef std::set<EventFilter::MatcherID> MatcherIDs;
  EventFilter& event_filter = g_event_filter.Get();
  std::string event_name = *v8::String::Utf8Value(args[0]);
  EventFilteringInfo info =
      ParseFromObject(args[1]->ToObject(isolate), isolate);
  MatcherIDs matched_event_filters = event_filter.MatchEvent(
      event_name, info, context()->GetRenderFrame()->GetRoutingID());
  v8::Local<v8::Array> array(
      v8::Array::New(isolate, matched_event_filters.size()));
  int i = 0;
  for (MatcherIDs::iterator it = matched_event_filters.begin();
       it != matched_event_filters.end();
       ++it) {
    array->Set(v8::Integer::New(isolate, i++), v8::Integer::New(isolate, *it));
  }
  args.GetReturnValue().Set(array);
}
