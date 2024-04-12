void InspectorTraceEvents::Init(CoreProbeSink* instrumenting_agents,
                                protocol::UberDispatcher*,
                                protocol::DictionaryValue*) {
  instrumenting_agents_ = instrumenting_agents;
  instrumenting_agents_->addInspectorTraceEvents(this);
}
