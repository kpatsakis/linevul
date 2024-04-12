void InspectorTraceEvents::DidReceiveResourceResponse(
    unsigned long identifier,
    DocumentLoader* loader,
    const ResourceResponse& response,
    Resource*) {
  LocalFrame* frame = loader ? loader->GetFrame() : nullptr;
  TRACE_EVENT_INSTANT1(
      "devtools.timeline", "ResourceReceiveResponse", TRACE_EVENT_SCOPE_THREAD,
      "data", InspectorReceiveResponseEvent::Data(identifier, frame, response));
  probe::AsyncTask async_task(frame ? frame->GetDocument() : nullptr,
                              AsyncId(identifier), "response");
}
