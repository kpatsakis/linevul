DEFINE_TRACE(InspectorPageAgent) {
  visitor->Trace(inspected_frames_);
  visitor->Trace(inspector_resource_content_loader_);
  InspectorBaseAgent::Trace(visitor);
}
