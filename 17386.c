void InspectorTraceEvents::Dispose() {
  instrumenting_agents_->removeInspectorTraceEvents(this);
  instrumenting_agents_ = nullptr;
}
