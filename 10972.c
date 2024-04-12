void InspectorPageAgent::FrameStoppedLoading(LocalFrame* frame) {
  GetFrontend()->frameStoppedLoading(IdentifiersFactory::FrameId(frame));
}
