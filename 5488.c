void InspectorPageAgent::FrameClearedScheduledNavigation(LocalFrame* frame) {
  GetFrontend()->frameClearedScheduledNavigation(
      IdentifiersFactory::FrameId(frame));
}
