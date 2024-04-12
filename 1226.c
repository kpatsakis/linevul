void InspectorTraceEvents::Did(const probe::ParseHTML& probe) {
  TRACE_EVENT_END1(
      "devtools.timeline", "ParseHTML", "endData",
      InspectorParseHtmlEndData(probe.parser->LineNumber().ZeroBasedInt() - 1));
  TRACE_EVENT_INSTANT1(TRACE_DISABLED_BY_DEFAULT("devtools.timeline"),
                       "UpdateCounters", TRACE_EVENT_SCOPE_THREAD, "data",
                       InspectorUpdateCountersEvent::Data());
}
